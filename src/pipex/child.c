/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:07:42 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/02 13:30:08 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	first_child(t_cmd *cmd)
{
	redir(0, cmd->pipefd[1], cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		redir(cmd->fd_infile, cmd->pipefd[1], cmd);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		redir(0, cmd->fd_outfile, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		redir(cmd->fd_infile, cmd->fd_outfile, cmd);
}

void	last_child(t_cmd *cmd)
{
	redir(cmd->pipefd[(cmd->i * 2) - 2], 1, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		redir(cmd->fd_infile, 1, cmd);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		redir(cmd->pipefd[(cmd->i * 2) - 2], cmd->fd_outfile, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		redir(cmd->fd_infile, cmd->fd_outfile, cmd);
}

void	middle_child(t_cmd *cmd)
{
	redir(cmd->pipefd[(cmd->i - 1) * 2], cmd->pipefd[(cmd->i * 2) + 1], cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		redir(cmd->fd_infile, cmd->pipefd[(cmd->i * 2) + 1], cmd);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		redir(cmd->pipefd[(cmd->i - 1) * 2], cmd->fd_outfile, cmd);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		redir(cmd->fd_infile, cmd->fd_outfile, cmd);
}

void	child(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (cmd->i == 0)
		first_child(cmd);
	else if (cmd->i == cmd->nbr_cmd - 1)
		last_child(cmd);
	else
		middle_child(cmd);
	close_all(cmd);
	if (check_builtin(cmd_lst, ms) == 1 && cmd_lst->test == 1)
	{
		find_path(cmd, envp, cmd_lst);
		if (cmd->i != 0 && cmd->cmd == NULL)
			free_cmd(cmd, envp, cmd_lst);
		if (cmd->i == 0 && cmd->cmd == NULL)
			free_cmd2(cmd, envp, cmd_lst);
	}
	else
		free_cmd2(cmd, envp, cmd_lst);
	if (execve(cmd->cmd, cmd->options, envp) == -1)
	{
		perror("Error fonction execve");
		free_cmd1(cmd);
		exit(127);
	}
}
