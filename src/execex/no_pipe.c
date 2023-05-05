/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:21:08 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/05 18:41:23 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fichier(t_cmd cmd, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	if (cmd_lst->outfile_name != NULL)
	{
		while (i < tab_len(cmd_lst->outfile_name) + 1 && cmd.tab_close_outfile[i] != -1 && cmd.tab_close_outfile[i] != 0)
		{
			if (close(cmd.tab_close_outfile[i]) == -1)
			{
				//printf("PB outfile close");
			}
			i++;
		}
	}
	i = 0;
	if (cmd_lst->infile_name != NULL)
	{
		while (i < tab_len(cmd_lst->infile_name) + 1 && cmd.tab_close_infile[i] != -1 && cmd.tab_close_infile[i] != 0)
		{
			if (close(cmd.tab_close_infile[i]) == -1)
			{
				//printf("PB infile close");
			}
			i++;
		}
	}
}

void	child_no_pipe(t_cmd *cmd, t_cmd_lst *cmd_lst, char **envp, t_ms *ms)
{
	redir(0, 1, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		redir(cmd->fd_infile, 1, cmd);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		redir(0, cmd->fd_outfile, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		redir(cmd->fd_infile, cmd->fd_outfile, cmd);
	if (check_builtin(cmd_lst, ms) == 1 && cmd_lst->test == 1)
	{
		find_path(cmd, envp, cmd_lst);
		if (cmd->cmd == NULL)
			free_cmd(cmd, envp, cmd_lst);
	}
	else
	{
		close_fichier(*cmd, cmd_lst);
		free_cmd2(cmd, envp, cmd_lst);
	}
	close_fichier(*cmd, cmd_lst);
	if (execve(cmd->cmd, cmd->options, envp) == -1)
	{
		perror("Error fonction execve");
		free_cmd1(cmd);
		exit(127);
	}
}

int	no_pipe2(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	clear_lst(&cmd_lst);
	if (cmd->tab_close_outfile != NULL)
		free(cmd->tab_close_outfile);
	if (cmd->tab_close_infile != NULL)
		free(cmd->tab_close_infile);
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
	init_tab_closefile(&cmd, cmd_lst);
	if (for_open(cmd_lst, &cmd, ms) != 1)
	{
		ms->cat_grep = check_cat_grep(cmd_lst, ms);
		cmd.off = fork();
		if (cmd.off == -1)
			error_management(2, &cmd);
		if (cmd.off == 0)
			child_no_pipe(&cmd, cmd_lst, (*ms).env, ms);
		only_last(cmd_lst, ms, &cmd, status);
		cmd.wpid = waitpid(cmd.off, &status, 0);
		if (cmd.wpid == -1)
			error_management(8, &cmd);
		if (WIFEXITED(status) != 0)
			cmd.exit_status = WEXITSTATUS(status);
	}
	close_fichier(cmd, cmd_lst);//close ici prendre en compte le -1 on close jusauq fin ou -1
	if (cmd_lst->limit_mode != NULL && cmd_lst->cmd_option[0] != NULL)
		if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
			if (unlink("/tmp/.file_temp.txt") == -1)
				error_management(7, &cmd);
	return (no_pipe2(&cmd, cmd_lst, ms));
}
