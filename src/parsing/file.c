/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/16 17:53:54 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_dbl_tab(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && bool_cote(str, i) == ERR)
		{
			while (str[i] == c)
				i++;
			count++;
		}
		i++;
	}
	if (count == 0)
		return (0);
	return (count + 1);
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
	char		*test;

	j = 0;
	k = 0;
	i = 0;
	if (nb_chevron(str, c) == 0)
		return (NULL);
	test = strdup(str);
	split_chevron = malloc(sizeof(char *) * (len_dbl_tab(str, c)));//protect malloc
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == c && bool_cote(test, i) == 1)
		{
			while ((str[i] == c && bool_cote(test, i) == ERR) || (str[i] == ' ' && bool_cote(test, i) == ERR))
			{
				str[i] = ' ';
				i++;
			}
			split_chevron[k] = malloc(sizeof(char) * (len_file(str, i, c) + 1));//protect malloc
			while ((str[i] != ' ' && str[i] != c && str[i] != '\0') || bool_cote(test, i) == 0)
			{
				split_chevron[k][j] = str[i];
				str[i] = ' ';
				i++;
				j++;
			}
			split_chevron[k][j] = '\0';
			k++;
		}
		if ((str[i] != '\0' && str[i] != c) || (str[i] == c && bool_cote(str, i) == SUC))
			i++;
	}
	split_chevron[k] = NULL;
	free(test);
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
		if (i != 0)
		{
			if ((str[i] == c && bool_cote(str, i) == ERR) && (str[i - 1] == c && bool_cote(str, i - 1) == ERR))
			{
				if (c == '>')
					(*ms)->boolean_outfile = 2;
				else if (c == '<')
					(*ms)->boolean_infile = 2;
				break ;
			}
		}
		if (str[i] == c && bool_cote(str, i) == ERR)
		{
			if (c == '>')
				(*ms)->boolean_outfile = 1;
			else if (c == '<')
				(*ms)->boolean_infile = 1;
			break ;
		}
		i--;
	}
	//printf("%d\n", (*ms)->boolean_infile);
}