/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:51 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/04 14:01:13 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_env(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "env") == SUC)
	{
		if (cmd_lst->cmd_option[1] != NULL)
			return (1);
		else
			env_builtin(ms);
		return (0);
	}
	return (1);
}

void	env_builtin(t_ms *ms)
{
	int	j;

	j = 0;
	while (ms->env[j] != NULL)
	{
		ft_printf(1, "%s", ms->env[j]);
		ft_printf(1, "\n");
		j++;
	}
}
