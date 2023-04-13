/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:40:25 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/13 10:52:56 by lgirault         ###   ########.fr       */
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
		i++;
	if (str[i] != '\0')
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

static int	space_chevron_utils(int *i, char *s, char c)
{
	while (s[*i] != '\0')
	{
		if (s[*i] == c && bool_cote(s, *i) == ERR)
		{
			if ((s[*i + 1] == '\0') || (s[*i + 2] == '\0')
				|| (s[*i + 2] == c && s[*i + 1] <= 32)
				|| ((s[*i + 1] == '<' || s[*i + 1] == '>') && s[*i + 2] == c))
				return (ERR);
			*i = *i + 1;
		}
		if (s[*i] != '\0')
			*i = *i + 1;
	}
	*i = 0;
	return (SUC);
}

int	check_space_chevron(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup(str);
	if (s == NULL)
		free_parsing(ms, cmd_lst, s);
	s = strspace_cpy(s, 0, &ms, cmd_lst);
	if (check_more_2_chevron(s) == ERR)
	{
		free(s);
		return (ERR);
	}
	if (space_chevron_utils(&i, s, '>') == ERR)
	{
		free(s);
		return (ERR);
	}
	if (space_chevron_utils(&i, s, '<') == ERR)
	{
		free(s);
		return (ERR);
	}
	free(s);
	return (SUC);
}
