/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:32:55 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/28 16:37:57 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	check_builtin(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "echo") == SUC)
	{
		if (ft_strcmp(cmd_lst->cmd_option[1], "-n") == SUC  && ft_strcmp(cmd_lst->cmd_option[2], "-e") != 0 && ft_strcmp(cmd_lst->cmd_option[2], "-E") != 0)
		{
			echo_builtin(cmd_lst->cmd_option, 1);
			return (0);
		}
		else if (ft_strcmp(cmd_lst->cmd_option[1], "-e") != 0 && ft_strcmp(cmd_lst->cmd_option[1], "-E") != 0 && ft_strcmp(cmd_lst->cmd_option[2], "-e") != 0 && ft_strcmp(cmd_lst->cmd_option[2], "-E") != 0)
		{
			echo_builtin(cmd_lst->cmd_option, 0);
			return (0);
		}
	}
	if (ft_strcmp(cmd_lst->cmd_option[0], "cd") == SUC)
		return (0);
	return (1);
}