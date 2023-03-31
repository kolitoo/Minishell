/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:40 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/31 17:35:27 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unset(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "unset") == SUC)
	{
		if (cmd_lst->cmd_option[1] == NULL)
			ft_printf("unset need argument\n");
		if (cmd_lst->cmd_option[1][0] == '-')
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

char	**unset_env(char *str, t_ms *ms)
{
	int	i;
	int	j;
	int	k;
	char	**new_env;

	i = 0;
	j = 0;
	k = 0;
	new_env = malloc(sizeof(char *) * (tab_len(ms->env) + 1));
	while (ms->env[j] != NULL)
	{
		if (strncmp(str, ms->env[j], ft_strlen(str)) == 0)
			j++;
	if (ms->env[j] == NULL)
		break;
	new_env[k] = malloc(sizeof(char) * (ft_strlen(ms->env[j]) + 1));
	while (ms->env[j][i] != '\0')
	{
		new_env[k][i] = ms->env[j][i];
		i++;
	}
	new_env[k][i] = '\0';
	i = 0;
	if (ms->env[j] != NULL)
	{
		k++;
		j++;
	}
	}
	new_env[k] = NULL;
	free(ms->env);
	return (new_env);
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
			ft_printf("unset: %s: invalid parameter name\n", cmd_lst->cmd_option[j]);
			break ;
		}
		else
			i++;
	}
	if (cmd_lst->cmd_option[j][i] == '\0')
		ms->env = unset_env(cmd_lst->cmd_option[j], ms);
	j++;
	}
	return (ms->env);
}