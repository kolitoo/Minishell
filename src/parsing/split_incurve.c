/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_incurve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:56:27 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 18:25:10 by lgirault         ###   ########.fr       */
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
	while ((str[i] != c || (str[i] == c && bool_cote(str, i) == SUC))
		&& str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static char	**split_incurve2(char *str, char **res, t_var var, char c)
{
	while (str[var.i] != '\0')
	{
		var.k = 0;
		while (str[var.i] == c && bool_cote(str, var.i) == ERR)
			var.i++;
		res[var.j] = malloc(sizeof(char) * (count_line(str, c, var.i) + 1));
		if (!res[var.j])
		{
			free_all(res, var.j);
			return (NULL);
		}
		while ((str[var.i] != c || (str[var.i] == c
					&& bool_cote(str, var.i) == SUC))
			&& str[var.i] != '\0')
		{
			res[var.j][var.k] = str[var.i];
			var.i++;
			var.k++;
		}
		res[var.j][var.k] = '\0';
		var.j++;
	}
	res[var.j] = NULL;
	return (res);
}

char	**split_incurve(char *str, char c)
{
	t_var	var;
	char	**res;

	var.i = 0;
	var.j = 0;
	res = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!res)
		return (NULL);//malloc
	res = split_incurve2(str, res, var, c);
	return (res);
}
