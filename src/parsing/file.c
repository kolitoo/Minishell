/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/15 23:23:16 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_dbl_tab(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c && bool_cote(str, i) == ERR)
			count++;
		i++;
	}
	return (count);
}

int	len_file(char *str, int i, char c)
{
	int	len;

	len = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ' ' || str[i] == c || str[i] == '\0') && bool_cote(str, i) == ERR)
			break;
		len++;
		i++;
	}
	return (len);
}

char	**find_file(char *str, char c)
{
	int		j;
	int		k;
	int		i;
	char		**split_chevron;

	j = 0;
	k = 0;
	i = 0;
	split_chevron = malloc(sizeof(char *) * (len_dbl_tab(str, c) + 1));//protect malloc
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == c && bool_cote(str, i) == 1)
		{
			while (str[i] == c || str[i] == ' ')
			{
				str[i] = ' ';
				i++;
			}
			split_chevron[k] = malloc(sizeof(char) * (len_file(str, i, c) + 1));//protect malloc
			while ((str[i] != ' ' && str[i] != c && str[i] != '\0') || bool_cote(str, i) == 0)
			{
				split_chevron[k][j] = str[i];
				str[i] = ' ';
				i++;
				j++;
			}
			split_chevron[k][j] = '\0';
			k++;
		}
		if (str[i] != '\0')
			i++;
	}
	split_chevron[k] = NULL;
	if (k == 0)
		split_chevron = NULL;
	return (split_chevron);
}

void	rights_check(char *str, t_ms **ms, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if ((str[i] == c && bool_cote(str, i) == ERR) && (str[i - 1] == c && bool_cote(str, i - 1) == ERR))
		{
			if (c == '>')
				(*ms)->boolean_outfile = 2;
			else if (c == '<')
				(*ms)->boolean_infile = 2;
			break ;
		}
		else if (str[i] == c && bool_cote(str, i) == ERR)
		{
			if (c == '>')
				(*ms)->boolean_outfile = 1;
			else if (c == '<')
				(*ms)->boolean_infile = 1;
			break ;
		}
		i--;
	}
}