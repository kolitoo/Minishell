/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/31 11:40:00 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char **find_file3(char *str, char **split_chevron, char *str2, t_var *var)
{
	if (str[var->i] == var->c && bool_cote(str2, var->i) == 1)
		{
			str = put_space(str, var->c, &var->i, str2);
			split_chevron[var->k] = malloc(sizeof(char)
					* (len_file(str, var->i, var->c) + 1));//protect malloc
			while ((str[var->i] != ' ' && str[var->i] != var->c && str[var->i] != '\0')
				|| bool_cote(str2, var->i) == 0)
			{
				split_chevron[var->k][var->j] = str[var->i];
				str[var->i] = ' ';
				var->i++;
				var->j++;
			}
			split_chevron[var->k][var->j] = '\0';
			if (var->j == 0)
				split_chevron[var->k] = NULL;
			var->k++;
		}
		return (split_chevron);
}

static char	**find_file2(char *str, char **split_chevron, char *str2, char c)
{
	t_var	var;

	var.j = 0;
	var.k = 0;
	var.i = 0;
	var.c = c;
	while (str[var.i] != '\0')
	{
		var.j = 0;
		split_chevron = find_file3(str, split_chevron, str2, &var);
		if ((str[var.i] != '\0' && str[var.i] != var.c)
			|| (str[var.i] == c && bool_cote(str, var.i) == SUC))
			var.i++;
	}
	split_chevron[var.k] = NULL;
	if (var.k == 0)
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
