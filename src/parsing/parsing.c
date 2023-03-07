/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/07 17:19:38 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_fine_cote(char *line, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			k = k * -1;
		i++;
	}
	if (k < 0)
		return (1);
	return (0);
}

int	check_cote(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	parsing(t_ms *ms)
{
	if (check_fine_cote(ms->line, '\'') == 0 && check_fine_cote(ms->line, '\"') == 0)
	{
		ms->line = strspace_cpy(ms->line, 0);
		ft_printf("line = %s\n", ms->line);
		if (check_cote(ms->line, '\'') == 0 && check_cote(ms->line, '\"') == 0)
		{
			
		}
		else
		{
			
		}
	}
	else
	{
		write(2, "Probleme cote\n", 15);
	}
}