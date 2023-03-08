/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:49:36 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/08 16:41:41 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	countlen(char *str)
{
	int	i;
	int	k;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (k == 0 || k == nb_cote(str))
		{
			if (str[i] == ' ')
			{
				while (str[i] == ' ' && str[i] != '\0')
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

char	*strspace_cpy(char *str, int i)
{
	int		j;
	int		k;
	char	*result;

	j = 0;
	k = 0;
	result = malloc(sizeof(char *) * (countlen(str) + 1));
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (k == 0 || k == nb_cote(str))
		{
			if (str[i] == ' ')
			{
				while ((str[i] == ' ') && str[i] != '\0')
					i++;
				if (str[i] > 32)
					result[j++] = ' ';
			}
		}
		if (str[i] == '\'' || str[i] == '\"')
			k++;
		if (str[i] == '\0')
			break ;
		if (str[i] != '\0')
			result[j++] = str[i];
		i++;
	}
	free(str);
	result[j] = '\0';
	return (result);
}