/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:16:37 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/11 10:19:05 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_outfile_trunc(t_cmd *cmd, t_cmd_lst *cmd_lst, int i)
{
	if (cmd_lst->outfile_mode == 1)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
	{
		file_error(9, cmd_lst, i);
		return (ERR);
	}
	return (SUC);
}

int	open_outfile_append(t_cmd *cmd, t_cmd_lst *cmd_lst, int i)
{
	if (cmd_lst->outfile_mode == 2)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
	{
		file_error(9, cmd_lst, i);
		return (ERR);
	}
	return (SUC);
}

int	open_outfile(t_cmd *cmd, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	if (cmd_lst->outfile_name != NULL)
	{
		while (cmd_lst->outfile_name[i] != NULL)
		{
			if (open_outfile_trunc(cmd, cmd_lst, i) == 1)
				return (ERR);
			if (open_outfile_append(cmd, cmd_lst, i) == 1)
				return (ERR);
			if (cmd_lst->outfile_mode == 3)
				open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			i++;
		}
	}
	return (SUC);
}
