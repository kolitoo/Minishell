/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:35:42 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/03 15:08:23 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	malloc_new_variable(char *variable, char *envstring, int *j)
{
	int	l;
	int	k;
	int	len;

	len = 0;
	l = 0;
	k = 0;
	while (envstring[*j] != '\0')
	{
		if (envstring[*j] == variable[k])
			k++;
		*j = *j + 1;
		if (variable[k] == '\0')
			break ;
	}
	l = *j;
	while (envstring[l] != '\0')
	{
		len++;
		l++;
	}
	return (len);
}

int	limit_mode_malloc(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			len++;
			i = i + 2;
		}
		if (str[i] == '<' && str[i + 1] != '<')
		{
			len++;
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (len);
}

int	len_dbl_tab(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && bool_cote(str, i) == ERR)
		{
			while (str[i] == c)
				i++;
			count++;
		}
		i++;
	}
	if (count == 0)
		return (0);
	return (count + 1);
}

int	len_file(char *str, int i, char c)
{
	int	len;

	len = 0;
	while (str[i] != '\0')
	{
		if ((str[i] <= ' ' || str[i] == c || str[i] == '\0')
			&& bool_cote(str, i) == ERR)
			break ;
		len++;
		i++;
	}
	return (len);
}
