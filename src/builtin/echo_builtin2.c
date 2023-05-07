/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:02:59 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 12:30:15 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_backslashzero(t_var *var, char *str, t_ms *ms, t_cmd_lst *cmd_lst)
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

static int	len_last_check(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i] != '\0')
	{
		if (((str[i] == '$' && str[i + 1] == '\'')
				|| (str[i] == '$' && str[i + 1] == '\"'))
			&& bool_cote(str, i) == ERR)
			i++;
		len++;
	}
	return (len);
}

char	*dollar_last_check(char *str, t_ms **ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	var.len = len_last_check(str);
	var.newstr = malloc(sizeof(char) * (var.len + 1));
	if (!var.newstr)
		free_parsing(*ms, cmd_lst, str);
	var.i = -1;
	while (str[++var.i] != '\0')
	{
		if (((str[var.i] == '$' && str[var.i + 1] == '\'')
				|| (str[var.i] == '$'
					&& str[var.i + 1] == '\"')) && bool_cote(str, var.i) == ERR)
			var.i++;
		var.newstr[var.j++] = str[var.i];
	}
	var.newstr[var.j] = '\0';
	free (str);
	return (var.newstr);
}
