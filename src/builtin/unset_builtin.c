/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:40 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/09 09:25:16 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unset(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "unset") == SUC)
	{
		if (cmd_lst->cmd_option[1] == NULL)
			ft_printf(2, "unset need argument\n");
		if (cmd_lst->cmd_option[1] != NULL && cmd_lst->cmd_option[1][0] == '-')
			return (1);
		return (0);
	}
	return (1);
}

int	pos_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

static char	**unset_env2(char *str, t_ms *ms, t_cmd_lst *cmd_lst, t_var var)
{
	while (ms->env[var.j] != NULL)
	{
		if (ft_strncmp(str, ms->env[var.j], pos_egal(str) + 1) == 0)
			var.j++;
		if (ms->env[var.j] == NULL)
			break ;
		var.tab[var.k] = malloc(sizeof(char) * (ft_strlen(ms->env[var.j]) + 1));
		if (var.tab[var.k] == NULL)
		{
			free(str);
			free_builtin_export(ms, cmd_lst, var.tab);
		}
		while (ms->env[var.j][var.i] != '\0')
		{
			var.tab[var.k][var.i] = ms->env[var.j][var.i];
			var.i++;
		}
		var.tab[var.k][var.i] = '\0';
		var.i = 0;
		if (ms->env[var.j++] != NULL)
			var.k++;
	}
	var.tab[var.k] = NULL;
	return (var.tab);
}

char	**unset_env(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	var.k = 0;
	var.tab = NULL;
	var.tab = malloc(sizeof(char *) * (tab_len(ms->env) + 2));
	if (var.tab == NULL)
		free_builtin_export(ms, cmd_lst, var.tab);
	str = ft_strjoin(str, "=");
	if (str == NULL)
		free_builtin_export(ms, cmd_lst, var.tab);
	var.tab = unset_env2(str, ms, cmd_lst, var);
	free(str);
	free_tab(ms->env, 0);
	return (var.tab);
}

char	**unset_builtin(t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (cmd_lst->cmd_option[j] != NULL)
	{
		i = 0;
		while (cmd_lst->cmd_option[j][i] != '\0')
		{
			if (cmd_lst->cmd_option[j][i] == '=')
			{
				ft_printf(2, "unset: %s: invalid parameter name\n",
					cmd_lst->cmd_option[j]);
				break ;
			}
			else
				i++;
		}
		if (check_if_unset(cmd_lst->cmd_option[j], ms) == 0)
			ms->env = unset_env(cmd_lst->cmd_option[j], ms, cmd_lst);
		j++;
	}
	return (ms->env);
}
