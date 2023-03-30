/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:49:14 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/30 14:38:12 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rights_check_util(char *str, int *i, t_ms **ms, char c)
{
	if ((str[*i] == '>' && bool_cote(str, *i) == ERR)
		&& (str[*i - 1] == '<' && bool_cote(str, *i - 1) == ERR))
	{
		(*ms)->boolean_outfile = 3;
		return (1);
	}
	else if ((str[*i] == c && bool_cote(str, *i) == ERR)
		&& (str[*i - 1] == c && bool_cote(str, *i - 1) == ERR))
	{
		if (c == '>')
			(*ms)->boolean_outfile = 2;
		else if (c == '<')
			(*ms)->boolean_infile = 2;
		return (1);
	}
	return (0);
}

char	*put_space(char *str, char c, int *i, char *str2)
{
	while ((str[*i] == c && bool_cote(str2, *i) == ERR)
		|| (str[*i] == ' ' && bool_cote(str2, *i) == ERR))
	{
		str[*i] = ' ';
		*i = *i + 1;
	}
	return (str);
}

int	her_doc_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (SUC);
		i++;
	}
	return (ERR);
}

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
