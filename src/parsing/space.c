/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:49:36 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/09 10:56:29 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	countlen(char *str, int i, int k, int count)
{
	while (str[i] <= ' ' && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (k == 0 || k == nb_cote(str))
		{
			if (str[i] <= ' ')
			{
				while (str[i] <= ' ' && str[i] != '\0')
					i++;
				if (str[i] != '\0')
					count++;
			}
		}
		if (str[i] == '\'' || str[i] == '\"')
			k++;
		if (str[i] == '\0')
			break ;
		count++;
		i++;
	}
	return (count);
}

static char	*strspace_cpy2(char *str, int i, int j, char *result)
{
	while (str[i] != '\0')
	{
		if (str[i] <= ' ' && bool_cote(str, i) == ERR)
		{
			while ((str[i] <= ' ') && str[i] != '\0')
				i++;
			if (str[i] > 32)
				result[j++] = ' ';
		}
		if (str[i] == '\0')
			break ;
		if (str[i] != '\0')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*strspace_cpy(char *str, int i, t_ms **ms, t_cmd_lst *cmd_lst)
{
	int		j;
	char	*result;

	j = 0;
	result = NULL;
	result = malloc(sizeof(char *)
			* (countlen(str, 0, 0, 0) + 1));
	if (!result)
		free_parsing(*ms, cmd_lst, str);
	while (str[i] <= ' ' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(result);
		return (str);
	}
	result = strspace_cpy2(str, i, j, result);
	free(str);
	return (result);
}
