/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:56:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/20 17:18:04 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//on a checker la validite des cotes avants donc aue des cas possibles
int	valid_cote(char *str, int i, char c)
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
	if ((k % 2) == 0) //pas entre cote
		return (ERR);
	return (SUC);
}

int	bool_cote(char *str, int i)
{
	int	one;
	int	two;

	one = valid_cote(str, i, '\'');
	two = valid_cote(str, i, '\"');
	if (one == ERR && two == SUC) //entre cote
		return (SUC);
	if (one == SUC && two == ERR) //entre cote
		return (SUC);
	if (one == SUC && two == SUC) //entre cote
		return (SUC);
	if (one == ERR && two == ERR) //pas entre cote
		return (ERR);
	return (ERR);
}

int	valid_cotev2(char *str, int i, char c)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j <= i)
	{
		if (str[j] == c)
			k++;
		j++;
	}
	if ((k % 2) == 0) //pas entre cote
		return (ERR);
	return (SUC);
}

int	bool_cotev2(char *str, int i)
{
	int	one;
	int	two;

	one = valid_cotev2(str, i, '\'');
	two = valid_cotev2(str, i, '\"');
	if (one == ERR && two == SUC) //entre cote
		return (SUC);
	if (one == SUC && two == ERR) //entre cote
		return (SUC);
	if (one == SUC && two == SUC) //entre cote
		return (SUC);
	if (one == ERR && two == ERR) //pas entre cote
		return (ERR);
	return (ERR);
}

int	nb_cote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	check_fine_cote(char *line, char c, char cote)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	while (line[i] != '\0')
	{
		if (line[i] == cote)
			k = k * -1;
		if (line[i] == c && k > 0)
		{
			i++;
			while (line[i] != c)
			{
				i++;
				if (line[i] == '\0')
					return (ERR);
			}
		}
		if (line[i] != '\0')
			i++;
	}
	if (k < 0)
		return (ERR);
	return (SUC);
}

int	check_cote(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (ERR);
		i++;
	}
	return (SUC);
}
