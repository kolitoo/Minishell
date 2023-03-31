/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:40:04 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/31 11:11:51 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exit(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC)
		return (0);
	return (1);
}

int	exit_builtin(t_cmd_lst *cmd_lst)
{
	while (cmd_lst->next != NULL)
	{
		cmd_lst = cmd_lst->next;
	}
	if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC)
		return (0);
	return (1);
}
