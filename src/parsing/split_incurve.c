/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_incurve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:56:27 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/14 11:22:52 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			i++;
		}
		if (str[i] && str[i] != c)
		{
			while (str[i])
			{
				i++;
				if (str[i] == c && bool_cote(str, i) == ERR)
					break ;
			}
			count++;
		}
	}
	return (count);
}

static void	free_all(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(res[i++]);
	free(res);
}

int	count_line(t_var var)
{
	int	count;

	count = 0;
	while ((var.newstr[var.i] != var.c || (var.newstr[var.i] == var.c
				&& bool_cote(var.newstr, var.i) == SUC))
		&& var.newstr[var.i] != '\0')
	{
		var.i++;
		count++;
	}
	return (count);
}

static char	**split_incurve2(char **res, t_var var,
			t_ms *ms, t_cmd_lst *cmd_lst)
{
	while (var.newstr[var.i] != '\0')
	{
		var.k = 0;
		while (var.newstr[var.i] == var.c
			&& bool_cote(var.newstr, var.i) == ERR)
			var.i++;
		res[var.j] = malloc(sizeof(char) * (count_line(var) + 1));
		if (!res[var.j])
		{
			free_all(res, var.j);
			free_parsing(ms, cmd_lst, var.newstr);
		}
		while ((var.newstr[var.i] != var.c || (var.newstr[var.i] == var.c
					&& bool_cote(var.newstr, var.i) == SUC))
			&& var.newstr[var.i] != '\0')
		{
			res[var.j][var.k] = var.newstr[var.i];
			var.i++;
			var.k++;
		}
		res[var.j][var.k] = '\0';
		var.j++;
	}
	res[var.j] = NULL;
	return (res);
}

char	**split_incurve(char *str, char c, t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;
	char	**res;

	var.i = 0;
	var.j = 0;
	var.c = c;
	var.newstr = str;
	res = malloc(sizeof(char *) * (count_words(var.newstr, var.c) + 1));
	if (!res)
		free_parsing(ms, cmd_lst, var.newstr);
	res = split_incurve2(res, var, ms, cmd_lst);
	return (res);
}
