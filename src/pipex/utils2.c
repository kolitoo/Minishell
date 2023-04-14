/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:06:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/14 11:58:20 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i - 1);
}

void	variable_util(t_var *var, char *str)
{
	if (str[var->k] == '$')
		var->k++;
	while ((str[var->k] >= 'a' && str[var->k] <= 'z')
		|| (str[var->k] >= 'A' && str[var->k] <= 'Z'))
		var->k++;
	while (str[var->k] != '\0')
		var->newstr[var->i++] = str[var->k++];
}
