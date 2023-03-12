/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:40:25 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/12 21:03:33 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_more_2_chevron(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
			if (str[i + 1] == '<' && str[i + 2] == '<')
				return (ERR);
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
			if (str[i + 1] == '>' && str[i + 2] == '>')
				return (ERR);
		i++;
	}
	return (SUC);
}

int	check_space_chevron(char *str)
{
	int	i;

	i = 0;
	if (check_more_2_chevron(str) == ERR)
		return (ERR);
	while (str[i] != '\0')
	{
		if (str[i] == '>' && bool_cote(str, i) == ERR)
		{
			if ((str[i + 2] == '>' && str[i + 1] <= 32) || (str[i + 1] == '<') || ((str[i + 1] == '<' || str[i + 1] == '>') && str[i + 2] == '<'))
				return (1);
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && bool_cote(str, i) == ERR)
		{
			if ((str[i + 2] == '<' && str[i + 1] <= 32) || ((str[i + 1] == '<' || str[i + 1] == '>') && str[i + 2] == '>'))
				return (1);
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (SUC);
}
