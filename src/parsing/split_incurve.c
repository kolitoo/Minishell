/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_incurve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:56:27 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/16 13:00:55 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			i++;
		}
		if (str[i] && str[i] != c)
		{
			while (str[i])
			{
				i++;
				if (str[i] == c && bool_cote(str, i) == ERR)
					break ;
			}
			count++;
		}
	}
	return (count);
}

static void	free_all(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(res[i++]);
	free(res);
}

int	count_line(char *str, char c, int i)
{
	int	count;

	count = 0;
	while ((str[i] != c || (str[i] == c && bool_cote(str, i) == SUC)) && str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

char	**split_incurve(char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!res)
		return (NULL);
	while (str[i] != '\0')
	{
		k = 0;
		while (str[i] == c && bool_cote(str, i) == ERR)
			i++;
		res[j] = malloc(sizeof(char) * (count_line(str, c, i) + 1));
		if (!res[j])
		{
			free_all(res, j);
			return (NULL);
		}
		while ((str[i] != c || (str[i] == c && bool_cote(str, i) == SUC)) && str[i] != '\0')
		{
			res[j][k] = str[i];
			i++;
			k++;
		}
		res[j][k] = '\0';
		j++;
	}
	res[j] = NULL;
	return (res);
}
