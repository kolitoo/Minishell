/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:40:25 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/14 14:38:22 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_chevron(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && bool_cote(str, i) == 1)
		{
			if (str[i + 1] == c && bool_cote(str, i) == 1 && str[i + 1] != '\0')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	check_after_chevron(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && bool_cote(str, i) == ERR)
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (SUC);
	i++;
	while (str[i] != '\0' && str[i] < 32)
	{
		i++;
	}
	i++;
	if (str[i] == '\0' || str[i] == '|' || str[i] == '\n')
		return (ERR);
	return (SUC);
}

int	check_more_2_chevron(char *str)
{
	int	i;

	i = 0;
	if (check_after_chevron(str) == ERR)
		return (ERR);
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
	char	*s;

	i = 0;
	s = ft_strdup(str);
	s = strspace_cpy(s, 0);
	if (check_more_2_chevron(s) == ERR)
	{
		free(s);
		return (ERR);
	}
	while (s[i] != '\0')
	{
		if (s[i] == '>' && bool_cote(s, i) == ERR)
		{
			if ((s[i + 2] == '>' && s[i + 1] <= 32) || (s[i + 1] == '<') || ((s[i + 1] == '<' || s[i + 1] == '>') && s[i + 2] == '<'))
			{
				free(s);
				return (ERR);
			}
			i++;
		}
		if (s[i] != '\0')
			i++;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '<' && bool_cote(s, i) == ERR)
		{
			if ((s[i + 2] == '<' && s[i + 1] <= 32) || ((s[i + 1] == '<' || s[i + 1] == '>') && s[i + 2] == '>'))
			{
				free(s);
				return (ERR);
			}
			i++;
		}
		if (s[i] != '\0')
			i++;
	}
	free(s);
	return (SUC);
}
