/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:32:38 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/04 15:56:10 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_outfile_heredoc(t_cmd *cmd, t_cmd_lst *cmd_lst, int i, int *j)
{
	if (cmd_lst->limit_mode != NULL)
	{
		if (cmd_lst->limit_mode[*j] == 2)
		{
			cmd->fd_infile = open("/tmp/.file_temp.txt", O_RDWR | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			read_prompt(cmd, cmd_lst, i);
			close(cmd->fd_infile);
			cmd->fd_infile = open("/tmp/.file_temp.txt", O_RDONLY);
			if (*j + 1 < tab_len(cmd_lst->infile_name))
				unlink("/tmp/.file_temp.txt");
			*j = *j + 1;
		}
		else
		{
			cmd->fd_infile = open(cmd_lst->infile_name[i], O_RDONLY);
			*j = *j + 1;
		}
	}
}

int	open_infile(t_cmd *cmd, t_cmd_lst *cmd_lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd_lst->infile_name != NULL)
	{
		while (cmd_lst->infile_name[i] != NULL)
		{
			if (cmd_lst->infile_mode == 1)
				cmd->fd_infile = open(cmd_lst->infile_name[i], O_RDONLY);
			open_outfile_heredoc(cmd, cmd_lst, i, &j);
			if (cmd->fd_infile == -1)
			{
				file_error(1, cmd_lst, i);
				return (ERR);
			}
			i++;
		}
	}
	return (SUC);
}
