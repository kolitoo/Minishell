/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:49:14 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/04 13:22:00 by lgirault         ###   ########.fr       */
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
		|| (str[*i] <= ' ' && bool_cote(str2, *i) == ERR))
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

char	**clean_str(char **double_tab, t_ms *ms, t_cmd_lst *cmd_lst)
{
	int	j;

	j = 0;
	while (double_tab[j] != NULL)
	{
		if (check_cote(double_tab[j], '\'') == ERR
			|| check_cote(double_tab[j], '\"') == ERR)
			double_tab[j] = clear_quote(double_tab[j], ms, cmd_lst);
		j++;
	}
	return (double_tab);
}

int	exist_chevron(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && bool_cote(str, i) == 1)
			return (0);
		i++;
	}
	return (1);
}
