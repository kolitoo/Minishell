/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:54:33 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/30 11:33:28 by abourdon         ###   ########.fr       */
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

char	*replace_variable(char *str, char *envstring, char *variable, int i)
{
	int		j;
	int		k;
	int		l;
	char	*newstr;
	char	*new_variable;

	j = -1;
	l = -1;
	new_variable = NULL;
	new_variable = neww_variable(new_variable, variable, envstring);
	newstr = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(variable)
				+ ft_strlen(new_variable)) + 1);//proteger malloc
	while (++l != i)
		newstr[l] = str[l];
	k = l;
	while (new_variable[++j] != '\0')
	{
		newstr[l] = new_variable[j];
		l++;
	}
	newstr = create_newstr(str, newstr, l, k);
	free(variable);
	free(new_variable);
	return (newstr);
}

char	*replace_variable2(char *str, char *variable, int i)
{
	int		j;
	int		k;
	int		l;
	char	*newstr;

	j = -1;
	l = -1;
	newstr = malloc(sizeof(char)
			* (ft_strlen(str) - ft_strlen(variable) + 1));//proteger malloc
	while (++l != i)
		newstr[l] = str[l];
	k = l;
	while (variable[++j] != '\0')
		k++;
	newstr = create_newstr(str, newstr, l, k);
	free(variable);
	return (newstr);
}

static char	*set_dollar2(char *str, int *i, t_ms **ms)
{
	if (str[*i] == '$' && str[*i + 1] == '?')
		str = warning_error(str, *i, ms);
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		while (str[*i] != '\"' && str[*i] != '\0')
		{
			if (str[*i] == '$' && ((str[*i + 1] >= 'a' && str[*i + 1] <= 'z')
					|| (str[*i + 1] >= 'A' && str[*i + 1] <= 'Z')))
			{
				str = comp_env(str, ms, *i);
				break ;
			}
			*i = *i + 1;
		}
		if (str[*i] == '\"' && str[*i] != '\0')
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
		str = set_dollar2(str, &i, ms);
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '$' && ((str[i + 1] >= 'a' && str[i + 1] <= 'z')
				|| (str[i + 1] >= 'A' && str[i + 1] <= 'Z')))
			str = comp_env(str, ms, i);
		if (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			i++;
	}
	return (str);
}
