/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:36:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/14 11:08:34 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char	**tab, int i)
{
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_builtin_export(t_ms *ms, t_cmd_lst *cmd_lst, char **new_envp)
{
	clear_lst(&cmd_lst);
	if (new_envp != NULL)
		free_tab(new_envp, 0);
	free_tab(ms->env, 0);
	rl_clear_history();
	exit(1);
}

void	free_builtin(t_ms *ms, t_cmd_lst *cmd_lst)
{
	clear_lst(&cmd_lst);
	free_tab(ms->env, 0);
	rl_clear_history();
	exit(1);
}

void	free_parsing(t_ms *ms, t_cmd_lst *cmd_lst, char *str)
{
	if (cmd_lst != NULL)
		clear_lst(&cmd_lst);
	free_tab(ms->env, 0);
	if (str != NULL)
		free (str);
	rl_clear_history();
	exit(1);
}

void	free_make_cmd_lst(t_ms *ms, t_cmd_lst *cmd_lst, char **double_tab)
{
	free(ms->split_pipe);
	free_tab(ms->env, 0);
	free_tab(double_tab, 0);
	if (cmd_lst != NULL)
		clear_lst(&cmd_lst);
	rl_clear_history();
	exit (1);
}
