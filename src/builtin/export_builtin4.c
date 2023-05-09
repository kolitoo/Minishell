/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:00:13 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 17:03:13 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pos_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+')
			return (i);
		i++;
	}
	return (0);
}

static int	check_forbiden_cara2(char *str, int i, int j)
{
	while (str[i] != '=' && str[i] != '\0')
	{
		if ((str[i] >= 0 && str[i] <= 35) || (str[i] >= 37 && str[i] < 43)
			|| (str[i] > 43 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 60)
			|| (str[i] >= 62 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 94)
			|| (str[i] == 96) || (str[i] >= 123 && str[i] <= 127))
			return (1);
		if ((str[i] >= 48 && str[i] <= 57))
		{
			j = i;
			while (j >= 0)
			{
				if ((str[j] >= 65 && str[j] <= 90)
					|| (str[j] >= 97 && str[j] <= 122))
					break ;
				j--;
			}
			if (j == -1)
				return (1);
		}
		if ((str[i] == '_') && i == 0 && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_forbiden_cara(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = 0;
	if (check_forbiden_cara2(str, i, j) == 1)
		return (1);
	return (0);
}
