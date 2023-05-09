/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:54:33 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/09 11:18:56 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_newstr(char *str, char *newstr, int l, int k)
{
	if (str[k] == '$')
		k++;
	while ((str[k] >= 'a' && str[k] <= 'z') || (str[k] >= 'A' && str[k] <= 'Z'))
		k++;
	while (str[k] != '\0')
		newstr[l++] = str[k++];
	newstr[l] = '\0';
	free(str);
	return (newstr);
}

char	*replace_variable(char *str, char *envstring, char *variable, int k)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	var.new_variable = NULL;
	var.new_variable = neww_variable(var.new_variable, variable, envstring);
	if (!var.new_variable)
		return (NULL);
	var.newstr = malloc(sizeof(char) * (ft_strlen(str)
				- ft_strlen(variable) + ft_strlen(var.new_variable)) + 1);
	if (!var.newstr)
	{
		free_env_utils(var.new_variable, variable, str, 0);
		return (NULL);
	}
	while (++var.i != k)
		var.newstr[var.i] = str[var.i];
	var.k = var.i;
	while (var.new_variable[var.j] != '\0')
		var.newstr[var.i++] = var.new_variable[var.j++];
	variable_util(&var, str);
	free_env_utils(var.new_variable, variable, str, 1);
	return (var.newstr);
}

char	*replace_variable2(char *str, char *variable, int k)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	var.newstr = malloc(sizeof(char)
			* (ft_strlen(str) - ft_strlen(variable) + 1));
	if (!var.newstr)
	{
		free_env_utils2(variable, str);
		return (NULL);
	}
	while (++var.i != k)
		var.newstr[var.i] = str[var.i];
	var.k = var.i;
	while (variable[var.j] != '\0')
	{
		var.k++;
		var.j++;
	}
	variable_util(&var, str);
	var.newstr[var.i] = '\0';
	free_env_utils2(variable, str);
	return (var.newstr);
}

static char	*set_dollar2(char *str, int *i, t_ms **ms, t_cmd_lst *cmd_lst)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		while (str[*i] != '\"' && str[*i] != '\0')
		{
			if (str[*i] == '$' && str[*i + 1] == '?')
			{
				str = warning_error(str, *i, ms, cmd_lst);
				*i = 0;
				break ;
			}
			if (str[*i] == '$' && str[*i + 1] != '\0' && str[*i + 1] > ' '
				&& str[*i + 1] != '\'' && str[*i + 1] != '\"' )
			{
				str = comp_env(str, ms, *i, cmd_lst);
				*i = 0;
			}
			*i = *i + 1;
		}
		if (str[*i] == '\"')
			*i = *i + 1;
	}
	set_dollar3(str, i);
	return (str);
}

char	*set_dollar(char *str, t_ms **ms, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			str = warning_error(str, i, ms, cmd_lst);
			i = 0;
		}
		str = set_dollar2(str, &i, ms, cmd_lst);
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] > ' '
			&& str[i + 1] != '\'' && str[i + 1] != '\"' )
		{
			str = comp_env(str, ms, i, cmd_lst);
			i = 0;
		}
		if (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			i++;
	}
	str = dollar_last_check(str, ms, cmd_lst);
	return (str);
}
