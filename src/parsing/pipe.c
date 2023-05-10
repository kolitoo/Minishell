/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:55:33 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 15:54:12 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_pipe2(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		while (str[*i] != '\"')
			*i = *i + 1;
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
}

static int	space_pipe_start(char *str, int *i)
{
	while ((str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		&& bool_cote(str, *i) == ERR)
		*i = *i + 1;
	if (str[*i] == '|')
		return (ERR);
	else
		return (SUC);
}

int	check_pipe(char *str, int i)
{
	if (space_pipe_start(str, &i) == ERR)
		return (ERR);
	check_pipe2(str, &i);
	while (str[i] != '\0')
	{
		if ((str[i] == '|' && bool_cote(str, i) == ERR)
			&& str[i + 1] == '\0')
			return (ERR);
		if ((str[i] == '|' && bool_cote(str, i) == ERR)
			&& str[i + 1] <= ' ')
		{
			i++;
			while (str[i] == ' ' || (str[i] >= 9
					&& str[i] <= 13))
				i++;
			if ((str[i] == '|' && bool_cote(str, i) == ERR)
				|| str[i] == '\0')
				return (ERR);
		}
		if (str[i] != '\0')
			i++;
	}
	return (SUC);
}
