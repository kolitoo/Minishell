/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/13 13:17:50 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pwd(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "pwd") == SUC)
	{
		if (cmd_lst->cmd_option[1] == NULL)
		{
			pwd_builtin(ms, cmd_lst);
			return (0);
		}
		else
		{
			ft_printf(2, "pwd: too many arguments\n");
			return (0);
		}
	}
	return (1);
}

void	pwd_builtin(t_ms *ms, t_cmd_lst *cmd_lst)
{
	char	*str;

	str = malloc(sizeof(char) * PATH_MAX + 1);//proteger
	if (str == NULL)
		free_builtin(ms, cmd_lst);
	getcwd(str, PATH_MAX);
	ft_printf(1, "%s\n", str);
}
