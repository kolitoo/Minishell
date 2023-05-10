/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:21:08 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 19:13:44 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_no_pipe(t_cmd *cmd, t_cmd_lst *cmd_lst, char **envp, t_ms *ms)
{
	sig_for_child();
	redir(0, 1, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		redir(cmd->fd_infile, 1, cmd);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		redir(0, cmd->fd_outfile, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		redir(cmd->fd_infile, cmd->fd_outfile, cmd);
	if (check_builtin(cmd_lst, ms, cmd) == 1)
	{
		find_path(cmd, envp, cmd_lst);
		if (cmd->cmd == NULL)
			free_cmd(cmd, envp, cmd_lst);
	}
	else
		free_cmd2(cmd, envp, cmd_lst);
	close_fichier(*cmd, cmd_lst, ms->env);
	if (execve(cmd->cmd, cmd->options, envp) == -1)
	{
		perror("Error fonction execve");
		free_cmd1(cmd);
		exit(127);
	}
}

int	no_pipe2(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms, int status)
{
	if (status == 2)
		cmd->exit_status = 130;
	else if (WIFEXITED(status) != 0)
			cmd->exit_status = WEXITSTATUS(status);
	if (access("/tmp/.file_temp.txt", F_OK) == 0)
		if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
			if (unlink("/tmp/.file_temp.txt") == -1)
				error_management(7, cmd);
	clear_lst(&cmd_lst);
	if (ms->builtin_code == 0)
		return (cmd->exit_status);
	else
		return (ms->builtin_code);
}

int	no_pipe(t_cmd_lst *cmd_lst, t_ms *ms)
{
	t_cmd	cmd;
	int		status;

	status = 0;
	init_tab(&cmd, cmd_lst);
	init_tab_closefile(&cmd, cmd_lst, ms);
	if (for_open(cmd_lst, &cmd, ms) != 1)
	{
		cmd.off = fork();
		if (cmd.off == -1)
			error_management(2, &cmd);
		else
			signal(SIGINT, SIG_IGN);
		if (cmd.off == 0)
			child_no_pipe(&cmd, cmd_lst, (*ms).env, ms);
		close_fichier(cmd, cmd_lst, ms->env);
		only_last(cmd_lst, ms, &cmd, status);
		cmd.wpid = waitpid(cmd.off, &status, 0);
		if (cmd.wpid == -1)
			error_management(8, &cmd);
		signal(SIGINT, handler_sigint);
	}
	return (no_pipe2(&cmd, cmd_lst, ms, status));
}
