/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:59:41 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/12 17:58:37 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *find_variable(char *str, int i)
{
    int        len;
    int        k;
    int        j;
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
    variable = malloc(sizeof(char) * (len + 2)); //protect
    if (!variable)
        return (NULL);
    while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        variable[k++] = str[i++];
    variable[k] = '=';
    variable[k + 1] = '\0';
    return (variable);
}

char    *neww_variable(char *new_variable, char *variable, char *envstring)
{
    int    i;
    int    j;

    i = 0;
    j = 0;
    new_variable = malloc(sizeof(char)
            * (malloc_new_variable(variable, envstring, &j) + 1));
    if (!new_variable)
        return (NULL);
    while (envstring[j] != '\0' && envstring[j] != '\n')
        new_variable[i++] = envstring[j++];
    new_variable[i] = '\0';
    return (new_variable);
}

static char    *warning_cpy(char *new_str, char *str, char *code_erreur, int i)
{
    int    k;
    int    j;

    k = 0;
    j = -1;
    while (++j < i)
        new_str[j] = str[j];
    while (str[i] != '\0')
    {
        k = 0;
        if (str[i] == '$' && str[i + 1] == '?')
        {
            i = i + 2;
            while (code_erreur[k] != '\0')
                new_str[j++] = code_erreur[k++];
        }
        if (str[i] != '\0')
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    free(str);
    free(code_erreur);
    return (new_str);
}

char    *warning_error(char *str, int i, t_ms **ms, t_cmd_lst *cmd_lst)
{
    int        j;
    int        len;
    char    *new_str;
    char    *code_erreur;

    j = 0;
    len = 0;
    new_str = NULL;
    code_erreur = NULL;
    code_erreur = ft_itoa((*ms)->code_erreur);
    if (!code_erreur)
        free_parsing(*ms, cmd_lst, str);
    while (str[j++] != '\0')
    {
        if (str[j] == '$' && str[j + 1] == '?')
            len = len + 2;
    }
    new_str = malloc(sizeof(char) * (ft_strlen(str) - len
                + ft_strlen(code_erreur) + 1));//protect malloc
    if (!new_str)
    {
        free(code_erreur);
        free_parsing(*ms, cmd_lst, str);
    }
    new_str = warning_cpy(new_str, str, code_erreur, i);
    return (new_str);
}

char    *comp_env(char *str, t_ms **ms, int i, t_cmd_lst *cmd_lst)
{
    int        j;
    char    *variable;

    variable = find_variable(str, i);
    if (!variable)
        free_parsing(*ms, cmd_lst, str);
    j = 0;
    while ((*ms)->env[j] != NULL)
    {
        if (strncmp((*ms)->env[j], variable, ft_strlen(variable)) == 0)
        {
            str = replace_variable(str, (*ms)->env[j], variable);
            if (!str)
                free_parsing(*ms, cmd_lst, str);
            break ;
        }
    j++;
    }
    if ((*ms)->env[j] == NULL)
    {
        str = replace_variable2(str, variable);
        if (!str)
            free_parsing(*ms, cmd_lst, str);
    }
    return (str);
}