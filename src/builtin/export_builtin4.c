/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:00:13 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 16:28:33 by abourdon         ###   ########.fr       */
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
