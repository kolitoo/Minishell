/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:02:59 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/05 16:04:10 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    check_backslashzero(t_var *var, char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
    if (str[var->i] == '\0')
    {
        var->newstr = malloc(sizeof(char) * 2);
        if (var->newstr == NULL)
            free_builtin(ms, cmd_lst);
        var->newstr[0] = '-';
        var->newstr[1] = '\0';
        free(str);
        return (1);
    }
    return (0);
}