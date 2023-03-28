/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:21:08 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/28 13:56:18 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_no_pipe(t_cmd *cmd, t_cmd_lst *cmd_lst, char **envp)
{
	redir(0, 1, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		redir(cmd->fd_infile, 1, cmd);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		redir(0, cmd->fd_outfile, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		redir(cmd->fd_infile, cmd->fd_outfile, cmd);
	if (check_builtin(cmd_lst) != 0)
	{
		printf("EXEC\n");
		find_path(cmd, envp, cmd_lst);
		if (cmd->cmd == NULL)
			free_cmd(cmd, envp, cmd_lst);
	}
	else
	{
		printf("BUILTIN\n");
		free_cmd(cmd, envp, cmd_lst);
	}
	if (execve(cmd->cmd, cmd->options, envp) == -1)
	{
		perror("Error fonction execve");
		free_cmd1(cmd);
		exit(127);
	}
}

int	no_pipe(t_cmd_lst *cmd_lst, char **envp)
{
	t_cmd cmd;
	int	status;

	init_tab(&cmd);
	if (for_open(cmd_lst, &cmd) != 1)
	{
		cmd.off = fork();
		if (cmd.off == -1)
			error_management(2, &cmd);
		if (cmd.off == 0)
		{
			child_no_pipe(&cmd, cmd_lst, envp);
		}
		cmd.wpid = waitpid(cmd.off, &status, 0);
		if (cmd.wpid == -1)
			error_management(8, &cmd);
		if (WIFEXITED(status) != 0)
			cmd.exit_status = WEXITSTATUS(status);
	}
	if (cmd_lst->limit_mode != NULL)
		if (cmd_lst->limit_mode[tab_len(cmd_lst)] == 2)
			if (unlink("/tmp/.file_temp.txt") == -1)
				error_management(7, &cmd);
	clear_lst(&cmd_lst);
	return (cmd.exit_status);
}