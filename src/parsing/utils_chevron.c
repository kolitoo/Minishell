/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:40:25 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/10 12:41:53 by lgirault         ###   ########.fr       */
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
				return (1);
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
			if (str[i + 1] == '>' && str[i + 2] == '>')
				return (1);
		i++;
	}
	return (0);
}

int	check_space_chevron(char *str)
{
	int	i;

	i = 0;
	if (check_more_2_chevron(str) == 1)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '>' && bool_cote(str, i) == 1)
		{
			if ((str[i + 2] == '>' && str[i + 1] <= 32) || (str[i + 1] == '<')  || ((str[i + 1] == '<' || str[i + 1] == '>') && str[i + 2] == '<'))
				return (1);
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && bool_cote(str, i) == 1)
		{
			if ((str[i + 2] == '<' && str[i + 1] <= 32) || ((str[i + 1] == '<' || str[i + 1] == '>') && str[i + 2] == '>'))
				return (1);
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (0);
}