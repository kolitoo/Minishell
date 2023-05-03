/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:59:56 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/02 17:34:33 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_management(int code_error, t_cmd *cmd)
{
	if (code_error == 2)
		perror("Error launch child procces");
	if (code_error == 3)
		write(2, "Number argument invalid\n", 24);
	if (code_error == 4)
		perror("Error fonction dup2");
	if (code_error == 5)
		perror("Error fonction pipe");
	if (code_error == 6)
		perror ("Error fonction close");
	if (code_error == 7)
		perror ("Error fonction unlink");
	if (code_error == 8)
		perror ("Error fonction waitpid");
	if (code_error != 3)
		free_cmd1(cmd);
	exit(EXIT_FAILURE);
}

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
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->pipefd != NULL)
		free(cmd->pipefd);
	if (cmd->pid)
		free(cmd->pid);
	lstclear(&cmd_lst);
	if (envp != NULL)
		free_tab(envp, 0);
	exit(127);
}
// if (cmd->options != NULL)
// 	free_tab(cmd->options, 0);
//enlever psk dans make_tab_path/find_path/ligne67 on dit cmd->options
// = cmd_lst->cmd_option donc il sera free quand on free la liste

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
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->pipefd != NULL)
		free(cmd->pipefd);
	if (cmd->pid)
		free(cmd->pid);
	lstclear(&cmd_lst);
	if (envp != NULL)
		free_tab(envp, 0);
	exit(0);
}
// if (cmd->options != NULL)
// 	free_tab(cmd->options, 0);
//enlever psk dans make_tab_path/find_path/ligne67 on dit cmd->options
// = cmd_lst->cmd_option donc il sera free quand on free la liste
