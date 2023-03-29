/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:40 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/29 16:56:52 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    **unset_env(char *str, t_ms *ms)
{
    int    i;
    int    j;
    int    k;
    char    **new_env;

    i = 0;
    j = 0;
    k = 0;
    new_env = malloc(sizeof(char *) * tab_len(ms->env));
    while (ms->env[j] != NULL)
    {
        if (strncmp(str, ms->env[j], ft_strlen(str)) == 0)
            j++;
        new_env[j] = malloc(sizeof(char) * (ft_strlen(ms->env[j]) + 1));
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