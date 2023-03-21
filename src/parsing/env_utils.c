/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:54:33 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/17 12:06:52 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_variable(char *str, int i)
{
	int	len;
	int	k;
	int	j;
	char	*variable;

	len = 0;
	k = 0;
	i++;
	j = i;
	while (str[j] != ' ' && str[j] != '\0' && str[j] != '\"' && str[j] != '\'' && str[i] != '$')
	{
		len++;
		j++;
	}
	variable = malloc(sizeof(char) * (len + 2));
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\"' && str[i] != '\'' && str[i] != '$')
	{
		variable[k] = str[i];
		k++;
		i++;
	}
	variable[k] = '=';
	variable[k + 1] = '\0';
	return (variable);	
}

char *neww_variable(char *new_variable, char *variable, char *envstring)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	len;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	l = 0;
	while (envstring[j] != '\0')
	{
		if (envstring[j] == variable[k])
			k++;
		j++;
		if (variable[k] == '\0')
			break ;
	}
	l = j;
	while (envstring[l] != '\0')
	{
		len++;
		l++;
	}
	new_variable = malloc(sizeof(char) * (len + 1));
	while (envstring[j] != '\0' && envstring[j] != '\n')
	{
		new_variable[i] = envstring[j];
		i++;
		j++;
	}
	new_variable[i] = '\0';
	return (new_variable);
}

char	*replace_variable(char *str, char *envstring, char *variable)
{
	int	i;
	int	j;
	int	k;
	char	*newstr;
	char	*new_variable;
	
	i = 0;
	j = 0;
	new_variable = NULL;
	new_variable = neww_variable(new_variable, variable, envstring);
	newstr = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(variable) + ft_strlen(new_variable)) + 1);
	while (str[i] != '$')
	{
		newstr[i] = str[i];
		i++;
	}
	k = i;
	while (new_variable[j] != '\0')
	{
		newstr[i] = new_variable[j];
		i++;
		j++;
	}
	while (str[k] != ' ' && str[k] != '\0' && str[k] != '\'' && str[k] != '\"')
		k++;
	while (str[k] != '\0')
	{
		newstr[i] = str[k];
		k++;
		i++;
	}
	newstr[i] = '\0';
	free(new_variable);
	free(variable);
	free(str);
	return (newstr);
}

char	*replace_variable2(char *str, char *variable)
{
	int	i;
	int	j;
	int	k;
	char	*newstr;
	
	i = 0;
	j = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(variable) + 1));
	while (str[i] != '$')
	{
		newstr[i] = str[i];
		i++;
	}
	k = i;
	while (variable[j] != '\0')
	{
		k++;
		j++;
	}
	while (str[k] != ' ' && str[k] != '\0' && str[k] != '\'' && str[k] != '\"')
		k++;
	while (str[k] != '\0')
	{
		newstr[i] = str[k];
		k++;
		i++;
	}
	newstr[i] = '\0';
	free(variable);
	free(str);
	return (newstr);
}

char	*comp_env(char *str, t_ms **ms, int i)
{
	int	j;
	char	*variable;

	variable = find_variable(str, i);//substr
	j = 0;
	printf("%s\n", variable);
	while ((*ms)->env[j] != NULL)
	{
		if (strncmp((*ms)->env[j], variable, ft_strlen(variable)) == 0)
		{
			str = replace_variable(str, (*ms)->env[j], variable);
			break ;
		}
		j++;
	}
	if ((*ms)->env[j] == NULL)
	{
		str = replace_variable2(str, variable);
	}
	return (str);
}

char	*set_dollar(char *str, t_ms **ms)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && valid_cote(str, i, '\'') == SUC)
		{
			if (valid_cote(str, i, '\"') == SUC)
			{
				str = comp_env(str, ms, i);
				i = 0;
			}
			i++;
		}
		else
		{
			if (str[i] == '$')
			{
				str = comp_env(str, ms, i);
				i = 0;
			}
			i++;
		}
	}
	return (str);
}