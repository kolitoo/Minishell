/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:36:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 16:25:24 by lgirault         ###   ########.fr       */
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

void	free_builtin(t_ms *ms, t_cmd_lst *cmd_lst, char **new_envp)
{
	clear_lst(&cmd_lst);//Peut etre a partir de i
	if (new_envp != NULL)
		free_tab(new_envp, 0);
	free_tab(ms->env, 0);
	exit(1);
}
