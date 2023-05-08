/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:56:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/08 16:19:09 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (str[j] == c)
	{
		if ((k % 2) == 1)
			k++;
	}
	if ((k % 2) == 0)
		return (ERR);
	return (SUC);
}

int	bool_cote(char *str, int i)
{
	int	one;
	int	two;

	one = valid_cote(str, i, '\'');
	two = valid_cote(str, i, '\"');
	if (one == ERR && two == SUC)
		return (SUC);
	if (one == SUC && two == ERR)
		return (SUC);
	if (one == SUC && two == SUC)
		return (SUC);
	if (one == ERR && two == ERR)
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
	t_var	var;

	var.i = 0;
	var.k = 1;
	while (line[var.i] != '\0')
	{
		if (line[var.i] == cote)
			var.k = var.k * -1;
		if (line[var.i] == c && var.k > 0)
		{
			var.i++;
			while (line[var.i] != c)
			{
				if (line[var.i] != '\0')
					var.i++;
				if (line[var.i] == '\0')
					return (ERR);
			}
		}
		if (line[var.i] != '\0')
			var.i++;
	}
	if (var.k < 0)
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
