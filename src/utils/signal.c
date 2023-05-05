/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:59:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/05 18:42:54 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	launch_signal(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	check_cat_grep(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "cat") == 0)
	{
		ms->lock_cat = 1;
		return (1);
	}
	if (ft_strcmp(cmd_lst->cmd_option[0], "grep") == 0 && cmd_lst->cmd_option[1] != NULL && cmd_lst->cmd_option[1][0] == '\0')
	{
		ms->lock_cat = 1;
		return (1);
	}
	return (0);
}