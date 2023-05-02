/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:40:04 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/02 12:22:42 by lgirault         ###   ########.fr       */
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

static int    ft_atoi(const char *str)
{
    int                i;
    int                sign;
    unsigned int    nb;

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
        nb = nb * 10 + str[i] - 48;
        i++;
    }
    return (sign * nb);
}

void	exit_builtin_execex(t_cmd_lst *cmd_lst, t_cmd *cmd,
	t_ms *ms, int status)
{
	int	arg_exit;
	
	arg_exit = 0;
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
		arg_exit = ft_atoi(cmd_lst->cmd_option[1]);
	clear_lst(&cmd_lst);
	free(ms->line);
	rl_clear_history();
	free_tab(ms->env, 0);
	exit (arg_exit);
	//exit (0);
}
