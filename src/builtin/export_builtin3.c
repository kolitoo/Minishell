/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:53:28 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 13:01:09 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_add(char *str, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_plus(str) == 0)
		return (2);
	while (ms->env[j] != NULL)
	{
		i = 0;
		while (str[i] != '+' && str[i + 1] != '=' && str[i] != '\0')
		{
			if (str[i] != ms->env[j][i])
				break ;
			i++;
		}
		if (str[i + 1] == ms->env[j][i])
			return (1);
		j++;
	}
	return (0);
}

char	**conca_env2(char *str, t_ms *ms, t_cmd_lst *cmd_lst, t_var var)
{
	free(var.new_variable);
	var.newstr = ft_substr(str, pos_plus(str) + 2,
			ft_strlen(str) - pos_plus(str));
	if (var.newstr == NULL)
		free_builtin(ms, cmd_lst);
	var.strfin = join2(ms->env[var.j], var.newstr);
	if (var.strfin == NULL)
		free_builtin(ms, cmd_lst);
	ms->env = replac_env(var.strfin, ms, cmd_lst, 1);
	free(var.strfin);
	return (ms->env);
}

char	**conca_env(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.j = 0;
	var.new_variable = ft_substr(str, 0, pos_plus(str) + 1);
	if (var.new_variable == NULL)
		free_builtin(ms, cmd_lst);
	var.new_variable[pos_plus(str)] = '=';
	while (ms->env[var.j] != NULL)
	{
		if (ft_strncmp(var.new_variable, ms->env[var.j],
				pos_egal(ms->env[var.j]) + 1) == 0)
		{
			ms->env = conca_env2(str, ms, cmd_lst, var);
			break ;
		}
		var.j++;
	}
	return (ms->env);
}
