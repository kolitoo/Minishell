/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:51:05 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/04 13:51:07 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_wd(char const *s, char c)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
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

static char	*gen_wd(const char *s, char c, int *i)
{
	int		j;
	char	*res;

	j = 0;
	while (s[*i] && s[*i] != c)
	{
		j++;
		*i += 1;
	}
	res = malloc((j + 1) * sizeof(char));
	if (!res)
		return (NULL);
	*i -= j;
	while (s[*i] && s[*i] != c)
	{
		*res++ = s[*i];
		*i += 1;
	}
	*res = '\0';
	return (res - j);
}

static void	free_all(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(res[i++]);
	free(res);
}

static char	**ft_split3(char **res, char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			res[j] = gen_wd(s, c, &i);
			if (!res[j++])
			{
				free_all(res, j);
				return (NULL);
			}
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split2(char const *s, char c)
{
	char	**res;

	res = NULL;
	if (s == NULL)
		return (NULL);
	res = malloc((count_wd(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_split3(res, s, c);
	return (res);
}
