/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cote2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:48:12 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/08 14:33:17 by abourdon         ###   ########.fr       */
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
	if ((k % 2) == 0)
		return (ERR);
	return (SUC);
}

int	bool_cotev2(char *str, int i)
{
	int	one;
	int	two;

	one = valid_cotev2(str, i, '\'');
	two = valid_cotev2(str, i, '\"');
	if (one == ERR && two == SUC)
		return (SUC);
	if (one == SUC && two == ERR)
		return (SUC);
	if (one == SUC && two == SUC)
		return (SUC);
	if (one == ERR && two == ERR)
		return (ERR);
	return (ERR);
}

static void	clear_quote2(char *str, int i, int *len)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			while (str[++i] != '\"')
				*len = *len + 1;
			if (str[i] == '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				*len = *len + 1;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
		{
			*len = *len + 1;
			i++;
		}
	}
}

static char	*clear_quote3(char *str, char *newstr, int i, int j)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				newstr[j++] = str[i++];
			if (str[i] == '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				newstr[j++] = str[i++];
			if (str[i] == '\'')
				i++;
		}
		if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
			newstr[j++] = str[i++];
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*clear_quote(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	int		i;
	int		j;
	int		len;
	char	*newstr;

	i = 0;
	j = 0;
	len = 0;
	clear_quote2(str, i, &len);
	newstr = malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		free_parsing(ms, cmd_lst, str);
	i = 0;
	newstr = clear_quote3(str, newstr, i, j);
	free(str);
	return (newstr);
}
