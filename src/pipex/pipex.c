/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:37:23 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 15:38:15 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	for_open(t_cmd_lst *cmd_lst, t_cmd *cmd, t_ms *ms)
{
	cmd->fd_infile = 0;
	cmd->fd_outfile = 0;
	if (open_infile(cmd, cmd_lst, ms) == ERR)
		return (ERR);
	if (open_outfile(cmd, cmd_lst, ms) == ERR)
		return (ERR);
	return (SUC);
}

void	init(t_cmd *cmd, t_cmd_lst *cmd_lst, char **envp)
{
	int	i;

	i = 0;
	cmd->i = 0;
	cmd->nbr_cmd = lstsize(cmd_lst);
	cmd->off = 2;
	cmd->pipefd = malloc(sizeof * cmd->pid * ((cmd->nbr_cmd - 1) * 2));
	if (cmd->pipefd == NULL)
		free_cmd(cmd, envp, cmd_lst);
	while (i < cmd->nbr_cmd - 1)
	{
		if (pipe(cmd->pipefd + 2 * i) == -1)
			error_management(5, cmd);
		i++;
	}
	cmd->pid = malloc(sizeof(int) * cmd->nbr_cmd);
	if (cmd->pid == NULL)
		free_cmd(cmd, envp, cmd_lst);
}
/*ON fait un pipe pour chaque paire de commande la
premiere fois on fait un pipe de 2 * 0*/

int	parent(t_cmd *cmd, t_ms *ms)
{
	int	status;

	cmd->i--;
	close_all(cmd);
	while (cmd->i >= 0)
	{
		cmd->wpid = waitpid(cmd->pid[cmd->i], &status, 0);
		if (cmd->wpid == -1)
			error_management(8, cmd);
		if (cmd->i == (cmd->nbr_cmd - 1) && WIFEXITED(status) != 0)
			cmd->exit_status = WEXITSTATUS(status);
		cmd->i--;
	}
	signal(SIGINT, handler_sigint);
	free(cmd->pipefd);
	free(cmd->pid);
	if (ms->builtin_code == 0)
		return (cmd->exit_status);
	else
		return (ms->builtin_code);
}

int	pipex(t_cmd_lst *cmd_lst, t_ms *ms)
{
	t_cmd	cmd;

	init_tab(&cmd, cmd_lst);
	init(&cmd, cmd_lst, (*ms).env);
	// init_tab_closefile(&cmd, cmd_lst, ms);
	// open_infile_heredoc(cmd, cmd_lst, ms);
	///check heredoc ici si pas ctrl c lance boucle sinon on quitte en supprimant le heredoc
	while (cmd_lst != NULL)
	{
		// printf("%s\n", cmd_lst->cmd_option[0]);
		// if (cmd_lst->infile_name != NULL)
		// {
		// 	printf("%s\n", cmd_lst->infile_name[0]);
		// }
		// if (cmd_lst->limit_mode != NULL)
		// {
		// 	printf("%d\n", cmd_lst->limit_mode[0]);
		// }
		//printf("%d\n", cmd_lst->limit_mode[0]);
		init_tab_closefile(&cmd, cmd_lst, ms);
		for_open(cmd_lst, &cmd, ms);
		if (ms->builtin_code != 130)
		{
			cmd.pid[cmd.i] = fork();
			if (cmd.pid[cmd.i] == -1)
				error_management(2, &cmd);
			else
				signal(SIGINT, SIG_IGN);
			if (cmd.pid[cmd.i] == 0)
			{
				sig_for_child();
				child(&cmd, (*ms).env, cmd_lst, ms);
			}
			close_fichier(cmd, cmd_lst, ms->env);
			only_last(cmd_lst, ms, &cmd, 1);
			if (access("/tmp/.file_temp.txt", F_OK) == 0)
				if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
					if (unlink("/tmp/.file_temp.txt") == -1)
						error_management(7, &cmd);
			clear_lst(&cmd_lst);
		}
		else
		{
			close_fichier(cmd, cmd_lst, ms->env);
			if (access("/tmp/.file_temp.txt", F_OK) == 0)
				if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
					if (unlink("/tmp/.file_temp.txt") == -1)
						error_management(7, &cmd);
			lstclear(&cmd_lst);
			break ;
		}
		cmd.i++;
	}
	return (parent(&cmd, ms));
}
