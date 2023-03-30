/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cote2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:48:12 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/30 16:07:31 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_cotev2(char *str, int i, char c)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j <= i)
	{
		if (str[j] == c)
			k++;
		j++;
	}
	if ((k % 2) == 0) //pas entre cote
		return (ERR);
	return (SUC);
}

int	bool_cotev2(char *str, int i)
{
	int	one;
	int	two;

	one = valid_cotev2(str, i, '\'');
	two = valid_cotev2(str, i, '\"');
	if (one == ERR && two == SUC) //entre cote
		return (SUC);
	if (one == SUC && two == ERR) //entre cote
		return (SUC);
	if (one == SUC && two == SUC) //entre cote
		return (SUC);
	if (one == ERR && two == ERR) //pas entre cote
		return (ERR);
	return (ERR);
}

static char	*clear_quote2(char *str, char *newstr, t_var *var, char c)
{
	var->i = var->i + 1;
	while (str[var->i] != c)
	{
		newstr[var->j] = str[var->i];
		var->i = var->i + 1;
		var->j = var->j + 1;
	}
	if (str[var->i] == c)
		var->i = var->i + 1;
	return (newstr);
}

char	*clear_quote(char *str)
{
	t_var	var;
	char	*newstr;

	var.i = 0;
	var.j = 0;
	newstr = malloc(sizeof(char)
			* (malloc_clear_quote(str, var.i) + 1));//proteger malloc
	while (str[var.i] != '\0')
	{
		if (str[var.i] == '\"')
			newstr = clear_quote2(str, newstr, &var, '\"');
		if (str[var.i] == '\'')
			newstr = clear_quote2(str, newstr, &var, '\'');
		if (str[var.i] != '\0' && str[var.i] != '\"' && str[var.i] != '\'')
		{
			newstr[var.j] = str[var.i];
			var.i++;
			var.j++;
		}
	}
	newstr[var.j] = '\0';
	free(str);
	return (newstr);
}
