/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:29 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 15:53:16 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_replace(char *str, t_ms *ms, int i, int bool)
{
	int	j;

	j = -1;
	if (bool == 0)
	{
		while (str[++j] != '+' && str[j + 1] != '=' && str[j] != '\0')
		{
			if (str[j] != ms->env[i][j])
				break ;
		}
		if (str[j + 1] == '=' && (str[j + 1] == ms->env[i][j]))
			return (1);
	}
	else
	{
		while (str[++j] != '=' && str[j] != '\0')
		{
			if (str[j] != ms->env[i][j])
				break ;
		}
		if (str[j] == '=' && (str[j] == ms->env[i][j]))
			return (1);
	}
	return (0);
}

int	check_crt_or_rplc(char *str, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->env[j] != NULL)
	{
		i = 0;
		while (str[i] != '=' && str[i] != '\0')
		{
			if (str[i] != ms->env[j][i])
				break ;
			i++;
		}
		if (str[i] == ms->env[j][i])
			return (0);
		j++;
	}
	return (1);
}

static	void	export_builtin2(t_cmd_lst *cmd_lst, t_ms *ms, int *i)
{
	if (check_add(cmd_lst->cmd_option[*i], ms) == 1)
		(*ms).env = conca_env(cmd_lst->cmd_option[*i], ms, cmd_lst);
	else if (check_add(cmd_lst->cmd_option[*i], ms) == 0)
		(*ms).env = create_env(cmd_lst->cmd_option[*i],
				ms, cmd_lst, 0);
	else if (check_crt_or_rplc(cmd_lst->cmd_option[*i], ms) == 1)
		(*ms).env = create_env(cmd_lst->cmd_option[*i],
				ms, cmd_lst, 1);
	else if (check_crt_or_rplc(cmd_lst->cmd_option[*i], ms) == 0)
		(*ms).env = replac_env(cmd_lst->cmd_option[*i],
				ms, cmd_lst, 1);
}

void	export_builtin(t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	i;

	i = 1;
	while (cmd_lst->cmd_option[i] != NULL)
	{
		if (check_forbiden_cara(cmd_lst->cmd_option[i]) == 0)
		{
			if (check_egal(cmd_lst->cmd_option[i]) == 0)
			{
				if ((cmd_lst->cmd_option[1][0] == '+'
					&& cmd_lst->cmd_option[1][1] == '=')
					|| cmd_lst->cmd_option[1][0] == '=')
					return (ms->builtin_code = 1, (void)0);
				else
					export_builtin2(cmd_lst, ms, &i);
			}
			else
				return (ms->builtin_code = 0, (void)0);
		}
		else
			ms->builtin_code = 1;
		i++;
	}
}
