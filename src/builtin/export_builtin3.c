/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:53:28 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/05 14:51:09 by lgirault         ###   ########.fr       */
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

static int    check_plus(char *str)
{
    int    i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '+' && str[i + 1] == '=')
            return (1);
        i++;
    }
    return (0);
}

int    check_add(char *str, t_ms *ms)
{
    int    i;
    int    j;

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
