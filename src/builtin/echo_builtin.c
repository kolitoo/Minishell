/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:35:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 15:52:42 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_n(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.i = 0;
	var.newstr = NULL;
	if (str[var.i] == '-')
		var.i++;
	else
		return (str);
	if (check_backslashzero(&var, str, ms, cmd_lst) == 1)
		return (var.newstr);
	while (str[var.i] == 'n')
		var.i++;
	if (str[var.i] != '\0')
		return (str);
	var.newstr = malloc(sizeof(char) * 3);
	if (var.newstr == NULL)
		free_builtin(ms, cmd_lst);
	var.newstr[0] = '-';
	var.newstr[1] = 'n';
	var.newstr[2] = '\0';
	free(str);
	return (var.newstr);
}

static int	check_e2(char *str)
{
	if (str == NULL)
		return (ERR);
	if (ft_strcmp(str, "-n") == SUC)
		return (ERR);
	if (str[0] != '-')
		return (ERR);
	return (SUC);
}

int	check_e(char *str, int i)
{
	if (check_e2(str) == ERR)
		return (ERR);
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == 'e' || str[i] == 'E')
		{
			i++;
			break ;
		}
		if (str[i] != 'n' && str[i] != 'e' && str[i] != 'E')
			return (ERR);
		i++;
	}
	while (str[i] == 'n' || str[i] == 'e' || str[i] == 'E')
		i++;
	if (str[i] == '\0')
		return (SUC);
	else
		return (ERR);
}

int	check_echo(t_cmd_lst *cmd_lst, t_ms *ms, int i, t_cmd cmd)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "echo") == SUC)
	{
		if (cmd_lst->cmd_option[1] == NULL || cmd_lst->cmd_option[1][0] == '\0')
		{
			echo_builtin(1, cmd_lst, ms, cmd);
			return (0);
		}
		cmd_lst->cmd_option[1] = check_n(cmd_lst->cmd_option[1], ms, cmd_lst);
		if (ft_strcmp(cmd_lst->cmd_option[1], "-n") == SUC
			&& check_e(cmd_lst->cmd_option[1], i) == ERR
			&& check_e(cmd_lst->cmd_option[2], i) == ERR)
		{
			echo_builtin(0, cmd_lst, ms, cmd);
			return (0);
		}
		else if (check_e(cmd_lst->cmd_option[1], i) == ERR
			&& check_e(cmd_lst->cmd_option[2], i) == ERR)
		{
			echo_builtin(1, cmd_lst, ms, cmd);
			return (0);
		}
	}
	return (1);
}

void	echo_builtin(int bool, t_cmd_lst *cmd_lst, t_ms *ms, t_cmd cmd)
{
	int	j;
	int	i;
	int	k;

	j = 1;
	i = 0;
	k = 0;
	while (cmd_lst->cmd_option[j] != NULL)
	{
		cmd_lst->cmd_option[j] = check_n(cmd_lst->cmd_option[j], ms, cmd_lst);
		if (ft_strcmp(cmd_lst->cmd_option[j], "-n") != SUC
			&& check_e(cmd_lst->cmd_option[j], i) == 1)
		{
			if (ft_printf(1, "%s", cmd_lst->cmd_option[j]) == -2)
			{
				k = 1;
				free_cmd4(&cmd, ms->env, cmd_lst);
			}
			if (cmd_lst->cmd_option[j + 1] != NULL)
				ft_printf(1, " ");
		}
		j++;
	}
	if (bool == 1 && k == 0)
		ft_printf(1, "\n");
}
