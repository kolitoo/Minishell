/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:32:55 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/29 16:58:13 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	check_builtin(t_cmd_lst *cmd_lst, char **envp)
{
	(void)envp;
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
	if (ft_strcmp(cmd_lst->cmd_option[0], "pwd") == SUC)
	{
		if (cmd_lst->cmd_option[1] == NULL)
		{
			pwd_builtin();
			return (0);
		}
		else
		{
			ft_printf("pwd: too many arguments\n");
			return (0);
		}
	}
	if (ft_strcmp(cmd_lst->cmd_option[0], "export") == SUC)
	{
		if (cmd_lst->cmd_option[1][0] == '-')
			return (1);
		return (0);
	}
	if (ft_strcmp(cmd_lst->cmd_option[0], "env") == SUC)
	{
		if (cmd_lst->cmd_option[1][0] == '-')
			return (1);
		return (0);
	}
	return (1);
}

void	only_last(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (cmd_lst->next == NULL && ft_strcmp(cmd_lst->cmd_option[0], "cd") == 0)
		cd_builtin(cmd_lst->cmd_option, (*ms).env);
	if (cmd_lst->next == NULL && ft_strcmp(cmd_lst->cmd_option[0], "export") == 0 && cmd_lst->cmd_option[1][0] != '-')
		export_builtin(cmd_lst, ms);
	if (ft_strcmp(cmd_lst->cmd_option[0], "env") == SUC && cmd_lst->cmd_option[1] == NULL)
		env_builtin(ms);
}