/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:51 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 15:52:58 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_env(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "env") == SUC)
	{
		if (cmd_lst->cmd_option[1] != NULL)
			return (1);
		else
			env_builtin(ms, cmd_lst);
		return (0);
	}
	return (1);
}

void	env_builtin(t_ms *ms, t_cmd_lst *cmd_lst)
{
	int		j;
	char	**print_env;

	j = 0;
	print_env = NULL;
	print_env = set_env(ms->env);
	print_env = clean_str(print_env, ms, cmd_lst);
	while (print_env[j] != NULL)
	{
		ft_printf(1, "%s", print_env[j]);
		ft_printf(1, "\n");
		j++;
	}
	free_tab(print_env, 0);
}
