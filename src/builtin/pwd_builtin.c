/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/05 11:22:15 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pwd(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "pwd") == SUC)
	{
		if (cmd_lst->cmd_option[1] == NULL)
		{
			pwd_builtin();
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

void	pwd_builtin(void)
{
	char	*str;

	str = malloc(sizeof(char) * PATH_MAX + 1);
	getcwd(str, PATH_MAX);
	ft_printf(1, "%s\n", str);
}
