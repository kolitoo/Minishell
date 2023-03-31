/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:54:33 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/31 14:04:33 by abourdon         ###   ########.fr       */
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

char    *replace_variable(char *str, char *envstring, char *variable)
{
    int    i;
    int    j;
    int    k;
    char    *newstr;
    char    *new_variable;
    
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

char    *replace_variable2(char *str, char *variable)
{
    int    i;
    int    j;
    int    k;
    char    *newstr;
    
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

char    *set_dollar(char *str, t_ms **ms)
{
    int    i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$' && str[i + 1] == '?')
        {
            str = warning_error(str, i, ms);
            i = 0;
        }
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
            {
                if (str[i] == '$')
                {
                    str = comp_env(str, ms, i);
                    i = 0;
                    break ;
                }
                i++;
            }
            if (str[i] == '\"')
                i++;
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
                i++;
            if (str[i] == '\'')
                i++;
        }
        if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '\'' && str[i + 1] != '\"' )
        {
            str = comp_env(str, ms, i);
            i = 0;
        }
        if (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
            i++;   
    }
    return (str);
}
