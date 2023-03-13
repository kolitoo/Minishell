/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:00:39 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/13 18:05:35 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_len(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && bool_cote(str, i) == 1)
		{
			while (str[i] == '<' || str[i] == ' ')
				i++;
			while (str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i] != '\0')
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	return (0);
}

char	*init_infile(char *str, int count)
{
	int	i;
	int	j;
	int	k;
	char	*s;
	char	*s2;

	i = 0;
	j = 0;
	k = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) - count) + 1);
	s2 = malloc(sizeof(char) * 10000);
	if (s == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		i = k;
		if ((str[i] == '<' && bool_cote(str, i) == ERR) || (str[i] <= 32 && str[i + 1] == '<' && bool_cote(str, i) == ERR))
		{
			if ((str[i] == '<' && bool_cote(str, i) == ERR))
				i = i + 2;
			else
				i = i + 3;
			while (str[i] != '\0' && (str[i] > 32 && bool_cote(str, i) == ERR))
				i++;
			if (str[i] != '\0')
				i++;
			while (str[i] != '\0')
			{
				s[j] = str[i];
				i++;
				j++;
			}
		}
		if (str[k] != '\0')
		{
			s2[k] = str[k];
			k++;
		}
	}
	s2[k] = '\0';
	s[j] = '\0';
	s = join(s2, s);
	free(str);
	return (s);
}

char	*find_infile(char *str, t_ms **ms, int i)
{
	char	*infile;
	int		j;
	int		count;

	j = 0;
	count = 0;
	infile = malloc(sizeof(char) * ft_len(str, i) + 1);
	infile[0] = '\0';
	if (infile == NULL)
	{
		(*ms)->infile_name = NULL;
		return (NULL);
	}
	while (str[i] != '\0')
	{
		if (str[i] == '<' && bool_cote(str, i) == 1)
		{
			if (i != 0 && str[i - 1] == ' ')
				count ++;
			while (str[i] == '<' || str[i] == ' ')
			{
				count++;
				i++;
			}
			while ((str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i] != '\0') || bool_cote(str, i) == 0)
			{
				infile[j] = str[i];
				i++;
				j++;
				count++;
			}
			infile[j] = '\0';
			(*ms)->infile_name = infile;
		}
		if (str[i] != '\0')
			i++;
	}
	if (infile[0] != '\0')
		str = init_infile(str, count);
	return (str);
}