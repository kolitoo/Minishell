/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tab_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:18:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/16 18:04:09 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	if (c <= 32)
		return (1);
	return (0);
}

int	count_word(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i] != '\0')
	{
		if (is_space(cmd[i]) == 0)
		{
			count++;
			while (is_space(cmd[i]) == 0)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**tab_option(char *cmd)
{
	char	**tab_option;

	tab_option = NULL;
	if (count_word(cmd) > 3)
		return (NULL);
	tab_option = ft_split(ft_strdup(cmd), ' ');
	if (tab_option == NULL)
		return (NULL);
	return (tab_option);
}
