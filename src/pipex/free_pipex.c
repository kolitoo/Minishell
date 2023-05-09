/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:59:56 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/09 09:51:53 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_lst(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*temp;

	temp = (*cmd_lst)->next;
	if ((*cmd_lst)->infile_name != NULL)
		free_tab((*cmd_lst)->infile_name, 0);
	if ((*cmd_lst)->outfile_name != NULL)
		free_tab((*cmd_lst)->outfile_name, 0);
	if ((*cmd_lst)->cmd_option != NULL)
		free_tab((*cmd_lst)->cmd_option, 0);
	if ((*cmd_lst)->limit_mode != NULL)
		free((*cmd_lst)->limit_mode);
	free(*cmd_lst);
	(*cmd_lst) = temp;
}

void	free_cmd(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	close_fichier(*cmd, cmd_lst, envp);
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->pipefd != NULL)
		free(cmd->pipefd);
	if (cmd->pid != NULL)
		free(cmd->pid);
	if (cmd_lst->cmd_option[0] == NULL)
	{
		lstclear(&cmd_lst);
		if (envp != NULL)
			free_tab(envp, 0);
		exit (0);
	}
	lstclear(&cmd_lst);
	if (envp != NULL)
		free_tab(envp, 0);
	exit(127);
}

void	free_cmd1(t_cmd *cmd)
{
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->options != NULL)
		free_tab(cmd->options, 0);
	if (cmd->pipefd != NULL)
		free(cmd->pipefd);
	if (cmd->pid != NULL)
		free(cmd->pid);
}

void	free_cmd2(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	close_fichier(*cmd, cmd_lst, envp);
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->pipefd != NULL)
		free(cmd->pipefd);
	if (cmd->pid != NULL)
		free(cmd->pid);
	lstclear(&cmd_lst);
	if (envp != NULL)
		free_tab(envp, 0);
	exit(0);
}

void	free_cmd4(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	close_fichier(*cmd, cmd_lst, envp);
	close_all(cmd);
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->pipefd != NULL)
		free(cmd->pipefd);
	if (cmd->pid != NULL)
		free(cmd->pid);
	lstclear(&cmd_lst);
	if (envp != NULL)
		free_tab(envp, 0);
	exit(1);
}
