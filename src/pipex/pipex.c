/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:37:23 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/22 14:39:31 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	for_open(t_cmd_lst *cmd_lst, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->fd_infile = 0;
	cmd->fd_outfile = 0;
	if (cmd_lst->infile_name != NULL)
	{
		while (cmd_lst->infile_name[i] != NULL)
		{
			if (cmd_lst->infile_mode == 1)
				cmd->fd_infile = open(cmd_lst->infile_name[i], O_RDONLY);
			if (cmd_lst->infile_mode == 2)//here_doc
				cmd->fd_infile = open(cmd_lst->infile_name[i], O_RDONLY);
			if (cmd->fd_infile == -1)
			{
				file_error(cmd, 1);
				return (ERR);
			}
			i++;
		}
	}
	i = 0;
	if (cmd_lst->outfile_name != NULL)
	{
		while (cmd_lst->outfile_name[i] != NULL)
		{
			if (cmd_lst->outfile_mode == 1)
				cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (cmd->fd_outfile == -1)
				cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (cmd->fd_outfile == -1)
			{
				file_error(cmd, 9);
				return(ERR);
			}
			if (cmd_lst->outfile_mode == 2)
				cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (cmd->fd_outfile == -1)
				cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (cmd->fd_outfile == -1)
			{
				file_error(cmd, 9);
				return (ERR);
			}
			i++;
		}
	}
	return (SUC);
}

// void	check_fd(char **argv, int argc, t_cmd *cmd)
// {
// 	// if (ft_strcmp(argv[1], "here_doc") == 0)
// 	// {
// 	// 	if (close(cmd->fd_infile) == -1)
// 	// 		error_management(6, cmd);
// 	// 	cmd->fd_infile = open(".file_temp.txt", O_RDONLY);
// 	// }
// 	cmd->fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC,
// 		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	cmd->fd_infile = open(argv[1], O_RDONLY);
// 	if (cmd->fd_outfile == -1)
// 		cmd->fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT,
// 				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	if (cmd->fd_infile == -1)
// 		file_error(cmd, 1);
// 	if (cmd->fd_outfile == -1)
// 		file_error(cmd, 9);
// }

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

void	child(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	find_path(cmd, envp, cmd_lst);
	if (cmd->i != 0 && cmd->cmd == NULL)
		free_cmd(cmd, envp, cmd_lst);
	if (cmd->i == 0 && cmd->cmd == NULL)
		free_cmd2(cmd, envp, cmd_lst);
	if (cmd->i == 0)
	{
		redir(0, cmd->pipefd[1], cmd);
		if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
			redir(cmd->fd_infile, cmd->pipefd[1], cmd);
		if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
			redir(0, cmd->fd_outfile, cmd);
		if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
			redir(cmd->fd_infile, cmd->fd_outfile, cmd);
	}
	else if (cmd->i == cmd->nbr_cmd - 1)
	{
		redir(cmd->pipefd[(cmd->i * 2) - 2], 1, cmd);
		if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
			redir(cmd->fd_infile, 1, cmd);
		if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
			redir(cmd->pipefd[(cmd->i * 2) - 2], cmd->fd_outfile, cmd);
		if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
			redir(cmd->fd_infile, cmd->fd_outfile, cmd);
	}
	else
	{
		redir(cmd->pipefd[(cmd->i - 1) * 2], cmd->pipefd[(cmd->i * 2) + 1], cmd);
		if (cmd->fd_infile != 0 && cmd->fd_outfile == 0)
			redir(cmd->fd_infile, cmd->pipefd[(cmd->i * 2) + 1], cmd);
		if (cmd->fd_infile == 0 && cmd->fd_outfile != 0)
			redir(cmd->pipefd[(cmd->i - 1) * 2], cmd->fd_outfile, cmd);
		if (cmd->fd_infile != 0 && cmd->fd_outfile != 0)
			redir(cmd->fd_infile, cmd->fd_outfile, cmd);
	}
	close_all(cmd);
	if (execve(cmd->cmd, cmd->options, envp) == -1)
	{
		perror("Error fonction execve");
		free_cmd1(cmd);
		exit(127);
	}
}

int	parent(t_cmd *cmd)
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
	// if (ft_strcmp(argv[1], "here_doc") == 0)
	// 	if (unlink(".file_temp.txt") == -1)
	// 		error_management(7, cmd);
	free(cmd->pipefd);
	free(cmd->pid);
	close_fd(cmd);
	return (cmd->exit_status);
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
	free(*cmd_lst);
	(*cmd_lst) = temp;
}

int	pipex(t_cmd_lst *cmd_lst, char **envp)
{
	t_cmd	cmd;

	init_tab(&cmd);
	cmd.argc = lstsize(cmd_lst);
	if (cmd.argc > 1)
	{
		init(&cmd, cmd_lst, envp);
		//here_doc(argc, argv, &cmd);
		//check_fd(argv, argc, &cmd);
		while (cmd_lst != NULL)//cmd.i < cmd.nbr_cmd
		{
			if (for_open(cmd_lst, &cmd) != 1)//envoie d'un seul element de la liste
			{
				cmd.pid[cmd.i] = fork();
				if (cmd.pid[cmd.i] == -1)
					error_management(2, &cmd);
				if (cmd.pid[cmd.i] == 0)
					child(&cmd, envp, cmd_lst);
			}
			clear_lst(&cmd_lst);
			cmd.i++;
		}
		parent(&cmd);
	}
	else
		error_management(3, &cmd);
	return (cmd.exit_status);
}
