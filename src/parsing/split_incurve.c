/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_incurve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:56:27 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/09 17:28:50 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_cote(char *str, int i, char c)//on a checker la validite des cotes avants donc aue des cas possibles
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j != i)
	{
		if (str[j] == c)
			k++;
		j++;
	}
	if ((k % 2) == 0)//pas entre cote
		return (1);
	return (0);
}

int	bool_cote(char *str, int i)
{
	int	one;
	int	two;

	one = valid_cote(str, i, '\'');
	two = valid_cote(str, i, '\"');
	if (one == 1 && two == 0)//entre cote
		return (0);
	if (one == 0 && two == 1)//entre cote
		return (0);
	if (one == 0 && two == 0)//entre cote
		return (0);
	if (one == 1 && two == 1)//pas entre cote
		return (1);
	return (1);
}

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
				if (str[i] == c && bool_cote(str, i) == 1)
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
	while ((str[i] != c || (str[i] == c && bool_cote(str, i) == 0)) && str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

char	**split_incurve(char *str, char c)
{
	int	i;
	int	j;
	int	k;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!res)
		return (NULL);
	while (str[i] != '\0')
	{
		k = 0;
		while (str[i] == c && bool_cote(str, i) == 1)
			i++;
		res[j] = malloc(sizeof(char) *  (count_line(str, c, i) + 1));
		if (!res[j])
		{
			free_all(res, j);
			return (NULL);
		}
		while ((str[i] != c || (str[i] == c && bool_cote(str, i) == 0)) && str[i] != '\0')
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
