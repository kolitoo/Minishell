/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:32:38 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 12:56:03 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_infile_heredoc(t_cmd *cmd, t_cmd_lst *cmd_lst, int *j, t_ms *ms)
{
	if (cmd_lst->limit_mode != NULL)
	{
		if (cmd_lst->limit_mode[*j] == 2)
		{
			cmd->fd_infile = open("/tmp/.file_temp.txt", O_RDWR | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			read_prompt(cmd, cmd_lst, ms);
			close(cmd->fd_infile);
			cmd->fd_infile = open("/tmp/.file_temp.txt", O_RDONLY);
			if (*j + 1 < tab_len(cmd_lst->infile_name))
				unlink("/tmp/.file_temp.txt");
			*j = *j + 1;
		}
		else
		{
			cmd->fd_infile
				= open(cmd_lst->infile_name[ms->i_heredoc], O_RDONLY);
			*j = *j + 1;
		}
	}
}

int	open_infile(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	j;

	ms->i_heredoc = 0;
	j = 0;
	if (cmd_lst->infile_name != NULL)
	{
		while (cmd_lst->infile_name[ms->i_heredoc] != NULL)
		{
			if (cmd_lst->infile_mode == 1)
				cmd->fd_infile
					= open(cmd_lst->infile_name[ms->i_heredoc], O_RDONLY);
			open_infile_heredoc(cmd, cmd_lst, &j, ms);
			if (cmd->fd_infile == -1)
			{
				file_error(1, cmd_lst, ms->i_heredoc);
				return (ERR);
			}
			if (ms->sig == 1)
			{
				return (ERR);
			}
			ms->i_heredoc++;
		}
	}
	return (SUC);
}
