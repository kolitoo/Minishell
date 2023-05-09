/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:29:09 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/09 10:43:16 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_closefile(t_cmd cmd, t_cmd_lst *cmd_lst, char **env)
{
	if (cmd.tab_close_outfile != NULL)
		free(cmd.tab_close_outfile);
	if (cmd.tab_close_infile != NULL)
		free(cmd.tab_close_infile);
	if (cmd.cmd != NULL)
		free(cmd.cmd);
	if (cmd.pipefd != NULL)
		free(cmd.pipefd);
	if (cmd.pid)
		free(cmd.pid);
	lstclear(&cmd_lst);
	if (env != NULL)
		free_tab(env, 0);
	exit (1);
}

static void	close_tab_out(t_cmd cmd, t_cmd_lst *cmd_lst, char **env)
{
	int	i;

	i = 0;
	(void)env;
	if (cmd_lst->outfile_name != NULL && cmd.tab_close_outfile != NULL)
	{
		while (i < tab_len(cmd_lst->outfile_name) + 1
			&& cmd.tab_close_outfile[i] != -1 && cmd.tab_close_outfile[i] != 0)
		{
			if (close(cmd.tab_close_outfile[i]) == -1)
			{
				ft_printf(2, "PB outfile close\n");
				free_closefile(cmd, cmd_lst, env);
			}
			i++;
		}
	}
}

static void	close_tab_in(t_cmd cmd, t_cmd_lst *cmd_lst, char **env)
{
	int	i;

	i = 0;
	(void)env;
	if (cmd_lst->infile_name != NULL && cmd.tab_close_infile != NULL)
	{
		while (i < tab_len(cmd_lst->infile_name) + 1
			&& cmd.tab_close_infile[i] != -1 && cmd.tab_close_infile[i] != 0)
		{
			if (close(cmd.tab_close_infile[i]) == -1)
			{
				ft_printf(2, "PB infile close\n");
				free_closefile(cmd, cmd_lst, env);
			}
			i++;
		}
	}
}

void	close_fichier(t_cmd cmd, t_cmd_lst *cmd_lst, char **env)
{
	close_tab_out(cmd, cmd_lst, env);
	close_tab_in(cmd, cmd_lst, env);
	if (cmd.tab_close_outfile != NULL)
		free(cmd.tab_close_outfile);
	if (cmd.tab_close_infile != NULL)
		free(cmd.tab_close_infile);
}
