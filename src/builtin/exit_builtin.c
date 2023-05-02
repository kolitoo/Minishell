/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:40:04 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/02 17:09:14 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exit(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC && (cmd_lst->cmd_option[2] == NULL || cmd_lst->cmd_option[1] == NULL))
	{
		cmd_lst->test = 0;
		return (0);
	}
	else if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC)
	{
		ft_printf(2, "exit: too many arguments\n");
		cmd_lst->test = 2;
		return (0);
	}
	cmd_lst->test = 1;
	return (1);
}

void	exit_builtin_pipex(t_cmd_lst *cmd_lst, t_cmd *cmd, t_ms *ms)
{
	if (cmd_lst->limit_mode != NULL)
		if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
			if (unlink("/tmp/.file_temp.txt") == -1)
				error_management(7, cmd);
	clear_lst(&cmd_lst);
	parent(cmd);
	rl_clear_history();
	free(ms->line);
	free_tab(ms->env, 0);
	exit (0);
}

static unsigned long long    ft_atoi(const char *str, t_ms *ms)
{
    int                i;
    int                sign;
    long long	nb;
    long long	old_nb;

    i = 0;
    sign = 1;
    nb = 0;
    while (str[i] == ' ' || str[i] == '\f'
        || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
    {
        i++;
    }
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= 48 && str[i] <= 57)
    {
	old_nb = nb;
        nb = nb * 10 + str[i] - 48;
	if (sign > 0)
	{
		if (nb < old_nb)
		{
			ms->builtin_code = 1;
			break ;
		}
	}
	else
		if (nb * -1 > old_nb * -1)
		{
			ms->builtin_code = 1;
			break ;
		}
        i++;
    }
    return (sign * nb);
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

void	exit_builtin_execex(t_cmd_lst *cmd_lst, t_cmd *cmd,
	t_ms *ms, int status)
{
	long long	arg_exit;
	
	arg_exit = 0;
	if (cmd_lst->cmd_option[1] != NULL && cmd_lst->cmd_option[2] != NULL)
	{
		ms->builtin_code = 1;
		return ;
	}
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
		if (check_nbr(cmd_lst->cmd_option[1]) == 1)
			arg_exit = 2;
		else
		{
			arg_exit = ft_atoi(cmd_lst->cmd_option[1], ms);
			if (ms->builtin_code != 0)
				arg_exit = 2;
		}
	}
	clear_lst(&cmd_lst);
	free(ms->line);
	rl_clear_history();
	free_tab(ms->env, 0);
	exit (arg_exit);
}
