/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:16:37 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 16:27:46 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_outfile_trunc(t_cmd *cmd, t_cmd_lst *cmd_lst, int i, t_ms *ms)
{
	if (cmd_lst->outfile_mode == 1)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
	{
		ms->builtin_code = 1;
		file_error(9, cmd_lst, i, *cmd);
		return (ERR);
	}
	cmd->tab_close_outfile[i] = cmd->fd_outfile;
	return (SUC);
}

int	open_outfile_append(t_cmd *cmd, t_cmd_lst *cmd_lst, int i, t_ms *ms)
{
	if (cmd_lst->outfile_mode == 2)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
		cmd->fd_outfile = open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (cmd->fd_outfile == -1)
	{
		ms->builtin_code = 1;
		file_error(9, cmd_lst, i, *cmd);
		return (ERR);
	}
	cmd->tab_close_outfile[i] = cmd->fd_outfile;
	return (SUC);
}

static int	check_infile(t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst->infile_name[i] != NULL)
	{
		if (access(cmd_lst->infile_name[i], F_OK | R_OK) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	open_outfile(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	i;

	i = 0;
	if (cmd_lst->outfile_name != NULL && check_infile(cmd_lst) == 0)
	{
		while (cmd_lst->outfile_name[i] != NULL)
		{
			if (open_outfile_trunc(cmd, cmd_lst, i, ms) == 1)
				return (ERR);
			if (open_outfile_append(cmd, cmd_lst, i, ms) == 1)
				return (ERR);
			if (cmd_lst->outfile_mode == 3)
				open(cmd_lst->outfile_name[i], O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			i++;
		}
	}
	return (SUC);
}
