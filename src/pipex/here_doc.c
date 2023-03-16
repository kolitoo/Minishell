/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:11:22 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/16 18:04:06 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_prompt(t_cmd *cmd, char **argv)
{
	char	*temp;

	while (1)
	{
		temp = get_next_line(0);
		if (temp == NULL)
		{
			free_cmd1(cmd);
			exit(1);
		}
		if (ft_strcmp_n(argv[2], temp) == 0)
			break ;
		write(cmd->fd_infile, temp, ft_strlen(temp));
		free(temp);
	}
	free(temp);
}

void	init_tab(t_cmd *cmd)
{
	cmd->pipefd = NULL;
	cmd->pid = NULL;
	cmd->cmd = NULL;
	cmd->options = NULL;
}

void	close_fd(t_cmd *cmd)
{
	if (cmd->fd_infile != -1)
		if (close(cmd->fd_infile) == -1)
			error_management(6, cmd);
	if (cmd->fd_outfile != -1)
		if (close(cmd->fd_outfile) == -1)
			error_management(6, cmd);
}

void	here_doc(int argc, char **argv, t_cmd *cmd)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		cmd->fd_infile = open(".file_temp.txt", O_RDWR | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		cmd->fd_outfile = open(argv[argc - 1],
				O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		read_prompt(cmd, argv);
	}
	else
	{
		cmd->fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		cmd->fd_infile = open(argv[1], O_RDONLY);
	}
}

int	where(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
