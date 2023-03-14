/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/14 18:30:59 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_len(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && bool_cote(str, i) == 1)
		{
			while (str[i] == '>' || str[i] == ' ')
				i++;
			while (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '\0')
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

// char	*init_outfile(char *str, int count)
// {
// 	int	i;
// 	char	*s;

// 	i = 0;
// 	s = malloc(sizeof(char) * (ft_strlen(str) - count) + 1);
// 	if (s == NULL)
// 		return (NULL);
// 	while (str[i] != '\0')
// 	{
// 		if ((str[i] == '>' && bool_cote(str, i) == ERR) || (str[i] <= 32 && str[i + 1] == '>' && bool_cote(str, i) == ERR))
// 			break ;
// 		s[i] = str[i];
// 		i++;
// 	}
// 	s[i] = '\0';
// 	free(str);
// 	return (s);
// }

int	len_before_chev(char *str)
{
	int	k;

	k = 0;
	while (str[k] != '\0')
	{
		if ((str[k] == ' ' && bool_cote(str, k) == ERR && str[k + 1] == '>' && bool_cote(str, k + 1) == ERR) || (str[k] == '>' && bool_cote(str, k) == ERR))
			break ;
		k++;
	}
	return (k);
}

char	*join2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlenn(s1) + ft_strlenn(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
	{
		str[j++] = s1[i];
	}
	free (s1);
	i = -1;
	while (s2[++i] != '\0')
	{
		str[j++] = s2[i];
	}
	str[j] = '\0';
	free(s2);
	free(s1);
	return (str);
}

char	*init_outfile(char *str, int count)
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
	s2 = malloc(sizeof(char) * (len_before_chev(str) + 1));//malloc a trouve
	if (s == NULL || s2 == NULL)
		return (NULL);
	while (str[k] != '\0')
	{
		if ((str[k] == ' ' && bool_cote(str, k) == ERR && str[k + 1] == '>' && bool_cote(str, k + 1) == ERR) || (str[k] == '>' && bool_cote(str, k) == ERR))
			break ;
		s2[k] = str[k];
		k++;
	}
	while (str[i] != '\0')
	{
		if ((str[i] == '>' && bool_cote(str, i) == ERR) || (str[i] <= 32 && str[i + 1] == '>' && bool_cote(str, i) == ERR))
		{
			if ((str[i] == '>' && bool_cote(str, i) == ERR))
				i = i + 2;
			else
				i = i + 3;
			while (str[i] != '\0' && (str[i] > 32 && bool_cote(str, i) == ERR))
				i++;
			while (str[i] != '\0')
			{
				s[j] = str[i];
				i++;
				j++;
			}
		}
		if (str[i] != '\0')
			i++;
	}
	s2[k] = '\0';
	s[j] = '\0';
	// printf("S2:%s$\n", s2);
	// printf("S:%s$\n", s);
	s = join2(s2, s);
	// printf("s2[0]%c\n", s2[0]);
	free(str);
	return (s);
}

char	*find_outfile_one(char *str, t_ms **ms, int i)
{
	char	*outfile;
	int		j;
	int		count;

	j = 0;
	count = 0;
	outfile = malloc(sizeof(char) * ft_len(str, i) + 1);
	outfile[0] = '\0';
	(*ms)->split_chevron = malloc(sizeof(char *) * 2);//verif malloc
	(*ms)->split_chevron[0] = malloc(sizeof(char) * ft_len(str, i) + 1);//trouver malloc
	if (outfile == NULL)
	{
		(*ms)->split_chevron = NULL;
		return (NULL);
	}
	while (str[i] != '\0')
	{
		if (str[i] == '>' && bool_cote(str, i) == 1)
		{
			if (i != 0 && str[i - 1] == ' ')
				count ++;
			while (str[i] == '>' || str[i] == ' ')
			{
				count++;
				i++;
			}
			while ((str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '\0') || bool_cote(str, i) == 0)
			{
				outfile[j] = str[i];
				i++;
				j++;
				count++;
			}
			outfile[j] = '\0';
			(*ms)->split_chevron[0] = outfile;
			(*ms)->split_chevron[1] = NULL;
		}
		if (str[i] != '\0')
			i++;
	}
	if (outfile[0] != '\0')
		str = init_outfile(str, count);//free dans init
	return (str);
}

char	*find_outfile(char *one_cmd, t_ms **ms)
{
	int	i;
	char	*s;

	i = 0;
	(*ms)->split_chevron = split_incurve(one_cmd, '>');// A faire dans find outfile et infile
	while ((*ms)->split_chevron[i] != NULL)
	{
		(*ms)->split_chevron[i] = ft_strtrim((*ms)->split_chevron[i], " ");//free dans trim
		i++;
	}
	s = ft_strdup((*ms)->split_chevron[0]);
	i = 0;
	while ((*ms)->split_chevron[i + 1] != NULL)
	{
		(*ms)->split_chevron[i] = ft_strdup((*ms)->split_chevron[i + 1]);
		i++;
	}
	(*ms)->split_chevron[i] = NULL;
	free(one_cmd);
	//print_map((*ms)->split_chevron);
	return (s);
}

void	rights_check(char *str, t_ms **ms, char c)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == c && bool_cote(str, i) == ERR) && (str[i + 1] == c && bool_cote(str, i + 1) == ERR))
		{
			if (c == '>')
				(*ms)->boolean_outfile = 2;
			else if (c == '<')
				(*ms)->boolean_infile = 2;
			break ;
		}
		else if (str[i] == c && bool_cote(str, i) == ERR)
		{
			if (c == '>')
				(*ms)->boolean_outfile = 1;
			else if (c == '<')
				(*ms)->boolean_infile = 1;
			break ;
		}
		i++;
	}
}