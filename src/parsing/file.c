/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/30 15:19:41 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**find_file2(char *str, char **split_chevron, char *str2, char c)
{
	int	j;
	int	k;
	int	i;

	j = 0;
	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == c && bool_cote(str2, i) == 1)
		{
			str = put_space(str, c, &i, str2);
			split_chevron[k] = malloc(sizeof(char)
					* (len_file(str, i, c) + 1));//protect malloc
			while ((str[i] != ' ' && str[i] != c && str[i] != '\0')
				|| bool_cote(str2, i) == 0)
			{
				split_chevron[k][j] = str[i];
				str[i] = ' ';
				i++;
				j++;
			}
			split_chevron[k][j] = '\0';
			if (j == 0)
				split_chevron[k] = NULL;
			k++;
		}
		if ((str[i] != '\0' && str[i] != c)
			|| (str[i] == c && bool_cote(str, i) == SUC))
			i++;
	}
	split_chevron[k] = NULL;
	if (k == 0)
		split_chevron = NULL;
	return (split_chevron);
}	

char	**find_file(char *str, char c)
{
	char		**split_chevron;
	char		*str2;

	if (nb_chevron(str, c) == 0)
		return (NULL);
	str2 = strdup(str);
	split_chevron = malloc(sizeof(char *) * (len_dbl_tab(str, c)));//protect malloc
	split_chevron = find_file2(str, split_chevron, str2, c);
	free(str2);
	return (split_chevron);
}

void	rights_check(char *str, t_ms **ms, char c)
{
	int	i;

	i = 0;
	if (c == '<')
		(*ms)->limit_mode = NULL;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (i != 0)
			if (rights_check_util(str, &i, ms, c) == 1)
				break ;
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
}

void	right_check_heredoc(char *str, t_ms **ms)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = limit_mode_malloc(str);
	(*ms)->limit_mode = malloc(sizeof(int) * len);//protect malloc
	while (str[i] != '\0')
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			(*ms)->limit_mode[j] = 2;
			j++;
			i = i + 2;
		}
		if (str[i] == '<' && str[i + 1] != '<')
		{
			(*ms)->limit_mode[j] = 1;
			j++;
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
}
