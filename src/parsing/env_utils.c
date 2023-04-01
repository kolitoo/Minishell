/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:54:33 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/01 19:33:52 by abourdon         ###   ########.fr       */
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

char	*replace_variable(char *str, char *envstring, char *variable)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	var.new_variable = NULL;
	var.new_variable = neww_variable(var.new_variable, variable, envstring);
	var.newstr = malloc(sizeof(char) * (ft_strlen(str)
				- ft_strlen(variable) + ft_strlen(var.new_variable)) + 1);
	while (str[++var.i] != '$')
		var.newstr[var.i] = str[var.i];
	var.k = var.i;
	while (var.new_variable[var.j] != '\0')
		var.newstr[var.i++] = var.new_variable[var.j++];
	if (str[var.k] == '$')
		var.k++;
	while ((str[var.k] >= 'a' && str[var.k] <= 'z')
		|| (str[var.k] >= 'A' && str[var.k] <= 'Z'))
		var.k++;
	while (str[var.k] != '\0')
		var.newstr[var.i++] = str[var.k++];
	var.newstr[var.i] = '\0';
	free(var.new_variable);
	free(variable);
	free(str);
	return (var.newstr);
}

char	*replace_variable2(char *str, char *variable)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	var.newstr = malloc(sizeof(char)
			* (ft_strlen(str) - ft_strlen(variable) + 1));
	while (str[++var.i] != '$')
		var.newstr[var.i] = str[var.i];
	var.k = var.i;
	while (variable[var.j] != '\0')
	{
		var.k++;
		var.j++;
	}
	if (str[var.k] == '$')
		var.k++;
	while ((str[var.k] >= 'a' && str[var.k] <= 'z')
		|| (str[var.k] >= 'A' && str[var.k] <= 'Z'))
		var.k++;
	while (str[var.k] != '\0')
		var.newstr[var.i++] = str[var.k++];
	var.newstr[var.i] = '\0';
	free(variable);
	free(str);
	return (var.newstr);
}

static char	*set_dollar2(char *str, int *i, t_ms **ms)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		while (str[*i] != '\"')
		{
			if (str[*i] == '$')
			{
				str = comp_env(str, ms, *i);
				*i = 0;
				break ;
			}
			*i = *i + 1;
		}
		if (str[*i] == '\"')
			*i = *i + 1;
	}
	if (str[*i] == '\'')
	{
		*i = *i + 1;
		while (str[*i] != '\'')
			*i = *i + 1;
		if (str[*i] == '\'')
			*i = *i + 1;
	}
	return (str);
}

char	*set_dollar(char *str, t_ms **ms)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			str = warning_error(str, i, ms);
			i = 0;
		}
		str = set_dollar2(str, &i, ms);
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' '
			&& str[i + 1] != '\'' && str[i + 1] != '\"' )
		{
			str = comp_env(str, ms, i);
			i = 0;
		}
		if (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			i++;
	}
	return (str);
}
