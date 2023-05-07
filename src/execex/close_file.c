/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:29:09 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 13:41:42 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_tab_out(t_cmd cmd, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	if (cmd_lst->outfile_name != NULL)
	{
		while (i < tab_len(cmd_lst->outfile_name) + 1
			&& cmd.tab_close_outfile[i] != -1 && cmd.tab_close_outfile[i] != 0)
		{
			if (close(cmd.tab_close_outfile[i]) == -1)
			{
				ft_printf(2, "PB outfile close\n");//gerer close echec
			}
			i++;
		}
	}
}

static void	close_tab_in(t_cmd cmd, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	if (cmd_lst->infile_name != NULL)
	{
		while (i < tab_len(cmd_lst->infile_name) + 1
			&& cmd.tab_close_infile[i] != -1 && cmd.tab_close_infile[i] != 0)
		{
			if (close(cmd.tab_close_infile[i]) == -1)
			{
				ft_printf(2, "PB infile close\n");//gerer close echec
			}
			i++;
		}
	}
}

void	close_fichier(t_cmd cmd, t_cmd_lst *cmd_lst)
{
	close_tab_out(cmd, cmd_lst);
	close_tab_in(cmd, cmd_lst);
	if (cmd.tab_close_outfile != NULL)
		free(cmd.tab_close_outfile);
	if (cmd.tab_close_infile != NULL)
		free(cmd.tab_close_infile);
}
