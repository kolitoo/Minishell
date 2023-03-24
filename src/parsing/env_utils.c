/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:54:33 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/24 11:27:50 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *find_variable(char *str, int i)
{
    int    len;
    int    k;
    int    j;
    char    *variable;

    len = 0;
    k = 0;
    i++;
    j = i;
    while ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z'))
    {
        len++;
        j++;
    }
    variable = malloc(sizeof(char) * (len + 2));
    while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
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
    int    i;
    int    j;
    int    k;
    int    l;
    int    len;

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

char    *replace_variable(char *str, char *envstring, char *variable, int i)
{
    int    j;
    int    k;
    int     l;
    char    *newstr;
    char    *new_variable;
    
    j = 0;
    l = 0;
    new_variable = NULL;
    new_variable = neww_variable(new_variable, variable, envstring);
    newstr = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(variable) + ft_strlen(new_variable)) + 1);
    while (l != i)
    {
        newstr[l] = str[l];
        l++;
    }
    k = l;
    while (new_variable[j] != '\0')
    {
        newstr[l] = new_variable[j];
        l++;
        j++;
    }
    while ((str[k] >= 'a' && str[k] <= 'z') || (str[k] >= 'A' && str[k] <= 'Z') || str[k] == '$')
        k++;
    while (str[k] != '\0')
    {
        newstr[l] = str[k];
        k++;
        l++;
    }
    newstr[l] = '\0';
    free(new_variable);
    free(variable);
    free(str);
    return (newstr);
}

char    *replace_variable2(char *str, char *variable, int i)
{
    int    j;
    int    k;
    int     l;
    char    *newstr;

    j = 0;
    l = 0;
    newstr = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(variable) + 1));
    while (l != i)
    {
        newstr[l] = str[l];
        l++;
    }
    k = l;
    while (variable[j] != '\0')
    {
        k++;
        j++;
    }
    while ((str[k] >= 'a' && str[k] <= 'z') || (str[k] >= 'A' && str[k] <= 'Z') || str[k] == '$')
        k++;
    while (str[k] != '\0')
    {
        newstr[l] = str[k];
        k++;
        l++;
    }
    newstr[l] = '\0';
    free(variable);
    free(str);
    return (newstr);
}

char    *comp_env(char *str, t_ms **ms, int i)
{
    int    j;
    char    *variable;

    variable = find_variable(str, i);
    j = 0;
    while ((*ms)->env[j] != NULL)
    {
        if (strncmp((*ms)->env[j], variable, ft_strlen(variable)) == 0)
        {
            str = replace_variable(str, (*ms)->env[j], variable, i);
            break ;
        }
        j++;
    }
    if ((*ms)->env[j] == NULL)
    {
        str = replace_variable2(str, variable, i);
    }
    return (str);
}

char    *warning_error(char *str, int i, t_ms **ms)
{
    char    *new_str;
    char    *code_erreur;
    int    j;
    int    k;
    int    len;
    
    j = 0;
    k = 0;
    len = 0;
    code_erreur = ft_itoa((*ms)->code_erreur);
    while (str[j] != '\0')
    {
        if (str[j] == '$' && str[j + 1] == '?')
            len = len + 2;
        j++;
    }
    j = 0;
    new_str = malloc(sizeof(char) * (ft_strlen(str) - len + ft_strlen(code_erreur) + 1));
    while (j < i)
    {
        new_str[j] = str[j];
        j++;
    }
    while (str[i] != '\0')
    {
        k = 0;
        if (str[i] == '$' && str[i + 1] == '?')
        {
            i = i + 2;
            while (code_erreur[k] != '\0')
            {
                new_str[j] = code_erreur[k];
                j++;
                k++;
            }
        }
        if (str[i] != '\0')
        {
            new_str[j] = str[i];
            j++;
            i++;
        }
    }
    new_str[j] = '\0';
    free(str);
    free(code_erreur);
    return (new_str);
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
            // i = 0;
        }
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"' && str[i] != '\0')
            {
                if (str[i] == '$' && ((str[i + 1] >= 'a' && str[i + 1] <= 'z') || (str[i + 1] >= 'A' && str[i + 1] <= 'Z')))
                {
                    str = comp_env(str, ms, i);
                    break ;
                }
                i++;
            }
            if (str[i] == '\"' && str[i] != '\0')
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
        if (str[i] == '$' && ((str[i + 1] >= 'a' && str[i + 1] <= 'z') || (str[i + 1] >= 'A' && str[i + 1] <= 'Z')))
            str = comp_env(str, ms, i);
        if (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
            i++;   
    }
    return (str);
}