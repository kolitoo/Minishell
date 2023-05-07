/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:40:04 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 12:43:40 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exit(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC
		&& (cmd_lst->cmd_option[1] == NULL || cmd_lst->cmd_option[2] == NULL))
	{
		if (cmd_lst->cmd_option[1] != NULL
			&& check_nbr(cmd_lst->cmd_option[1]) == 1)
			ft_printf(2, "exit: numeric argument required\n");
		return (0);
	}
	else if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC
		&& check_nbr(cmd_lst->cmd_option[1]) == 1)
	{
		ft_printf(2, "exit: numeric argument required\n");
		return (0);
	}
	else if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC)
	{
		ft_printf(2, "exit: too many arguments\n");
		return (0);
	}
	return (1);
}

unsigned long long	ft_atoi(const char *str, t_ms *ms)
{
	t_atoi	var;

	var.i = 0;
	var.sign = 1;
	var.nb = 0;
	while (str[var.i] == ' ' || str[var.i] == '\f'
		|| str[var.i] == '\t' || str[var.i] == '\n'
		|| str[var.i] == '\r' || str[var.i] == '\v')
	{
	var.i++;
	}
	if (str[var.i] == '-' || str[var.i] == '+')
	{
		if (str[var.i] == '-')
			var.sign *= -1;
		var.i++;
	}
	ft_atoi2(&var, ms, str);
	return (var.sign * var.nb);
}

int	check_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] == '-' && str[i + 1] != '\0')
			i++;
		if (i == 0 && str[i] == '+' && str[i + 1] != '\0')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	str_is_dig(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	exit_builtin_execex(t_cmd_lst *cmd_lst, t_cmd *cmd,
	t_ms *ms, int status)
{
	long long	arg_exit;

	arg_exit = 0;
	if (cmd_lst->cmd_option[1] != NULL && cmd_lst->cmd_option[2] != NULL
		&& str_is_dig(cmd_lst->cmd_option[1]) == 0)
		return (ms->builtin_code = 1, (void)0);
	cmd->wpid = waitpid(cmd->off, &status, 0);
	if (cmd->wpid == -1)
		error_management(8, cmd);
	if (WIFEXITED(status) != 0)
		cmd->exit_status = WEXITSTATUS(status);
	if (cmd_lst->limit_mode != NULL)
		if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
			if (unlink("/tmp/.file_temp.txt") == -1)
				error_management(7, cmd);
	if (cmd_lst->cmd_option[1] != NULL)
	{
		arg_exit = ft_atoi(cmd_lst->cmd_option[1], ms);
		if (check_nbr(cmd_lst->cmd_option[1]) == 1)
			arg_exit = 2;
		else
			if (ms->builtin_code != 0)
				arg_exit = 2;
	}
	exit_builtin_free(cmd_lst, ms, arg_exit, *cmd);
}
