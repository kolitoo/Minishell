/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:26:03 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/03 11:23:02 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_atoi2(t_atoi *var, t_ms *ms, const char *str)
{
	while (str[var->i] >= 48 && str[var->i] <= 57)
	{
		var->old_nb = var->nb;
		var->nb = var->nb * 10 + str[var->i] - 48;
		if (var->sign > 0)
		{
			if (var->nb < var->old_nb)
			{
				ms->builtin_code = 1;
				break ;
			}
		}
		else
		{
			if (var->nb * -1 > var->old_nb * -1)
			{
				ms->builtin_code = 1;
				break ;
			}
		}
	var->i++;
	}
}

void	exit_builtin_free(t_cmd_lst *cmd_lst, t_ms *ms, long long arg_exit)
{
	clear_lst(&cmd_lst);
	free(ms->line);
	rl_clear_history();
	free_tab(ms->env, 0);
	exit (arg_exit);
}
