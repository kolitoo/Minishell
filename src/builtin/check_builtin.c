/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:32:55 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/05 11:21:45 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtin(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (check_echo(cmd_lst) == SUC)
		return (0);
	if (check_cd(cmd_lst) == SUC)
		return (0);
	if (check_pwd(cmd_lst) == SUC)
		return (0);
	if (ft_strcmp(cmd_lst->cmd_option[0], "export") == SUC)
	{
		if (cmd_lst->cmd_option[1] == NULL)
			ft_printf(2, "export need argument\n");
		if (cmd_lst->cmd_option[1][0] == '-')
			return (1);
		return (0);
	}
	if (check_env(cmd_lst, ms) == SUC)
		return (0);
	if (check_unset(cmd_lst) == SUC)
		return (0);
	if (check_exit(cmd_lst) == SUC)
		return (0);
	return (1);
}

void	only_last(t_cmd_lst *cmd_lst, t_ms *ms, t_cmd *cmd, int status)
{
	if (cmd_lst->next == NULL && ft_strcmp(cmd_lst->cmd_option[0], "cd") == 0)
		cd_builtin(cmd_lst->cmd_option, (*ms).env);
	if (cmd_lst->next == NULL && ft_strcmp(cmd_lst->cmd_option[0],
			"export") == 0 && cmd_lst->cmd_option[1] != NULL
		&& cmd_lst->cmd_option[1][0] != '-')
		export_builtin(cmd_lst, ms);
	if (cmd_lst->next == NULL && ft_strcmp(cmd_lst->cmd_option[0],
			"unset") == SUC && cmd_lst->cmd_option[1] != NULL
		&& cmd_lst->cmd_option[1][0] != '-')
		unset_builtin(cmd_lst, ms);
	if (status == 0 && cmd_lst->next == NULL
		&& ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC)
		exit_builtin_execex(cmd_lst, cmd, ms, status);
	if (status == 1 && cmd_lst->next == NULL
		&& ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC)
		exit_builtin_pipex(cmd_lst, cmd, ms);
}
