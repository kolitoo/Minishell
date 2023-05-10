/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:07:42 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 18:44:34 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	first_child(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	if (redir(0, cmd->pipefd[1], cmd) == 1)
		free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		if (redir(cmd->fd_infile, cmd->pipefd[1], cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		if (redir(0, cmd->fd_outfile, cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		if (redir(cmd->fd_infile, cmd->fd_outfile, cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
}

void	last_child(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	if (redir(cmd->pipefd[(cmd->i * 2) - 2], 1, cmd) == 1)
		free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		if (redir(cmd->fd_infile, 1, cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		if (redir(cmd->pipefd[(cmd->i * 2) - 2], cmd->fd_outfile, cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		if (redir(cmd->fd_infile, cmd->fd_outfile, cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
}

void	middle_child(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	if (redir(cmd->pipefd[(cmd->i - 1) * 2],
			cmd->pipefd[(cmd->i * 2) + 1], cmd) == 1)
		free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
		if (redir(cmd->fd_infile, cmd->pipefd[(cmd->i * 2) + 1], cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
		if (redir(cmd->pipefd[(cmd->i - 1) * 2], cmd->fd_outfile, cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
	if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
		if (redir(cmd->fd_infile, cmd->fd_outfile, cmd) == 1)
			free_cmd4(cmd, envp, cmd_lst);
}

void	exit_exec(t_cmd *cmd, t_cmd_lst *cmd_lst)
{
	perror("Error fonction execve");
	free_cmd1(cmd);
	lstclear(&cmd_lst);
	exit(127);
}

void	child(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst, t_ms *ms)
{
	sig_for_child();
	if (cmd->i == 0)
		first_child(cmd, envp, cmd_lst);
	else if (cmd->i == cmd->nbr_cmd - 1)
		last_child(cmd, envp, cmd_lst);
	else
		middle_child(cmd, envp, cmd_lst);
	close_all(cmd);
	if (check_builtin(cmd_lst, ms, cmd) == 1)
	{
		find_path(cmd, envp, cmd_lst);
		if (cmd->i != 0 && cmd->cmd == NULL)
			free_cmd(cmd, envp, cmd_lst);
		if (cmd->i == 0 && cmd->cmd == NULL)
			free_cmd2(cmd, envp, cmd_lst);
	}
	else
		free_cmd2(cmd, envp, cmd_lst);
	close_fichier(*cmd, cmd_lst, ms->env);
	if (execve(cmd->cmd, cmd->options, envp) == -1)
		exit_exec(cmd, cmd_lst);
}
