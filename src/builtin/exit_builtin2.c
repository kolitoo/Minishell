/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:26:03 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 13:09:23 by lgirault         ###   ########.fr       */
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

void	exit_builtin_free(t_cmd_lst *cmd_lst, t_ms *ms,
			long long arg_exit, t_cmd cmd)
{
	close_fichier(cmd, cmd_lst, ms->env);
	if (cmd.tab_close_outfile != NULL)
		free(cmd.tab_close_outfile);
	if (cmd.tab_close_infile != NULL)
		free(cmd.tab_close_infile);
	clear_lst(&cmd_lst);
	free(ms->line);
	rl_clear_history();
	free_tab(ms->env, 0);
	ft_printf(1, "exit\n");
	exit (arg_exit);
}

void	exit_builtin_pipex(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (cmd_lst->cmd_option[1] != NULL && cmd_lst->cmd_option[2] != NULL
		&& str_is_dig(cmd_lst->cmd_option[1]) == 0)
		return (ms->builtin_code = 1, (void)0);
	if (cmd_lst->cmd_option[1] != NULL)
	{
		ms->builtin_code = ft_atoi(cmd_lst->cmd_option[1], ms);
		if (check_nbr(cmd_lst->cmd_option[1]) == 1)
			ms->builtin_code = 2;
	}
}
