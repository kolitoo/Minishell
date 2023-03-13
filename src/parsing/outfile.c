/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/13 17:53:20 by lgirault         ###   ########.fr       */
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

char	*init_outfile(char *str, int count)
{
	int	i;
	char	*s;

	i = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) - count) + 1);
	if (s == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if ((str[i] == '>' && bool_cote(str, i) == ERR) || (str[i] <= 32 && str[i + 1] == '>' && bool_cote(str, i) == ERR))
			break ;
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	free(str);
	return (s);
}

char	*find_outfile(char *str, t_ms **ms, int i)
{
	char	*outfile;
	int		j;
	int		count;

	j = 0;
	count = 0;
	outfile = malloc(sizeof(char) * ft_len(str, i) + 1);
	outfile[0] = '\0';
	if (outfile == NULL)
	{
		(*ms)->outfile_name = NULL;
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
			(*ms)->outfile_name = outfile;
		}
		if (str[i] != '\0')
			i++;
	}
	if (outfile[0] != '\0')
		str = init_outfile(str, count);//free dans init
	return (str);
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