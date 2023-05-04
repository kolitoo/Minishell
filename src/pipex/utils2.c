/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:06:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/04 13:59:24 by lgirault         ###   ########.fr       */
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
	var->newstr[var->i] = '\0';
}

int	check_if_unset(char *str, t_ms *ms)
{
	int		i;
	int		j;
	char	*s1;

	i = 0;
	j = 0;
	while (ms->env[i] != NULL)
	{
		s1 = ft_substr(ms->env[i], 0, pos_egal(ms->env[i]));
		if (ft_strcmp(s1, str) == 0)
		{
			free (s1);
			return (0);
		}
		i++;
		free (s1);
	}
	return (1);
}
