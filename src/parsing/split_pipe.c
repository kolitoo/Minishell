/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:22:43 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/09 11:25:10 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_wd_cote(char *s, char c, int i, int nb)
{
	int	j;
	int	l;

	l = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			while (l != nb_cote(s) && s[i] != '\0')
			{
				if (l == '\'' || l == '\"')
					l++;
				i++;
			}
			nb++;
			if (s[i] != '\0')
				i++;
		}
		while (s[i] && s[i] != c)
		{
			j++;
			i++;
		}
		if (j)
			nb += 1;
	}
	return (nb);
}

static int	count_line(char *str, char c, int i)
{
	int	len;
	int	l;

	len = 0;
	l = 1;
	while (str[i] != c && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			len++;
			while (l != nb_cote(str) && str[i] != '\0')
			{
				if (l == '\'' || l == '\"')
					l++;
				len++;
				i++;
			}
		}
		if (str[i] != '\0')
			i++;
		if (str[i] != '\0')
			len++;
	}
	return (len);
}

static void	free_all(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(res[i++]);
	free(res);
}

char	**split_pipe(char *str, char c)
{
	int	i;
	int	j;
	int	k;
	int	l;
	char **res;

	j = 0;
	i = 0;
	l = 1;
	res = malloc(sizeof(char *) * (count_wd_cote(str, c, 0, 0) + 1));
	if (!res)
		return (NULL);
	while (str[i] != '\0')
	{
		k = 0;
		while (str[i] && str[i] == c)
			i++;
		res[j] = malloc(sizeof(char) * (count_line(str, c, i) + 1));
		if (!res[j])
		{
			free_all(res, j);
			return (NULL);
		}
		if (str[i] && str[i] != c)
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				res[j][k] = str[i];
				k++;
				i++;
				while (l < nb_cote(str))
				{
					if (str[i] == '\'' || str[i] == '\"')
						l++;
					res[j][k] = str[i];
					k++;
					i++;
				}
				res[j][k] = str[i];
			}
			while (str[i] && str[i] != c)
			{
				res[j][k] = str[i];
				k++;
				i++;
			}
		}
		res[j][k] = '\0';
		j++;
	}
	res[j] = NULL;
	return (res);
}