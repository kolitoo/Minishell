/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:37:23 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/16 18:12:55 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_fd(char **argv, int argc, t_cmd *cmd)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (close(cmd->fd_infile) == -1)
			error_management(6, cmd);
		cmd->fd_infile = open(".file_temp.txt", O_RDONLY);
	}
	if (cmd->fd_outfile == -1)
		cmd->fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_infile == -1)
		file_error(cmd, 1);
	if (cmd->fd_outfile == -1)
		file_error(cmd, 9);
}

void	init(t_cmd *cmd, char **argv, int argc)
{
	int	i;

	i = 0;
	cmd->i = 0;
	cmd->nbr_cmd = argc - 3;
	cmd->off = 2;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		cmd->off = 3;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		cmd->nbr_cmd = argc - 4;
	cmd->pipefd = malloc(sizeof * cmd->pid * ((cmd->nbr_cmd - 1) * 2));
	if (cmd->pipefd == NULL)
		free_cmd(cmd);
	while (i < cmd->nbr_cmd - 1)
	{
		if (pipe(cmd->pipefd + 2 * i) == -1)
			error_management(5, cmd);
		i++;
	}
	cmd->pid = malloc(sizeof(int) * cmd->nbr_cmd);
	if (cmd->pid == NULL)
		free_cmd(cmd);
}
/*ON fait un pipe pour chaque paire de commande la
premiere fois on fait un pipe de 2 * 0*/

void	child(t_cmd *cmd, char **envp, char **argv)
{
	find_path(cmd, envp, argv);
	if (cmd->i != 0 && cmd->cmd == NULL)
		free_cmd(cmd);
	if (cmd->i == 0 && cmd->cmd == NULL)
		free_cmd2(cmd);
	if (cmd->i == 0)
		redir(cmd->fd_infile, cmd->pipefd[1], cmd);
	else if (cmd->i == cmd->nbr_cmd - 1)
		redir(cmd->pipefd[(cmd->i * 2) - 2], cmd->fd_outfile, cmd);
	else
		redir(cmd->pipefd[(cmd->i - 1) * 2],
			cmd->pipefd[(cmd->i * 2) + 1], cmd);
	close_all(cmd);
	if (execve(cmd->cmd, cmd->options, envp) == -1)
	{
		perror("Error fonction execve");
		free_cmd1(cmd);
		exit(127);
	}
}

void	parent(t_cmd *cmd, char **argv)
{
	int	status;
	int	exit_status;

	cmd->i--;
	close_all(cmd);
	while (cmd->i >= 0)
	{
		cmd->wpid = waitpid(cmd->pid[cmd->i], &status, 0);
		if (cmd->wpid == -1)
			error_management(8, cmd);
		if (cmd->i == (cmd->nbr_cmd - 1) && WIFEXITED(status) != 0)
			exit_status = WEXITSTATUS(status);
		cmd->i--;
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		if (unlink(".file_temp.txt") == -1)
			error_management(7, cmd);
	free(cmd->pipefd);
	free(cmd->pid);
	close_fd(cmd);
	exit(exit_status);
}

int	pipex(t_cmd_lst *cmd_lst)//envoie env
{
	t_cmd	cmd;

	init_tab(&cmd);
	cmd.argv = argv;
	if (argc > 4)
	{
		if (ft_strcmp(argv[1], "here_doc") == 0)
			if (argc <= 5)
				error_management(3, &cmd);
		init(&cmd, argv, argc);
		here_doc(argc, argv, &cmd);
		check_fd(argv, argc, &cmd);
		while (cmd.i < cmd.nbr_cmd)
		{
			cmd.pid[cmd.i] = fork();
			if (cmd.pid[cmd.i] == -1)
				error_management(2, &cmd);
			if (cmd.pid[cmd.i] == 0)
				child(&cmd, envp, argv);
			cmd.i++;
		}
		parent(&cmd, argv);
	}
	else
		error_management(3, &cmd);
}
