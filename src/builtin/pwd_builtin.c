/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 13:47:30 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pwd(t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "pwd") == SUC)
	{
		pwd_builtin(ms, cmd_lst);
		return (0);
	}
	return (1);
}

void	pwd_builtin(t_ms *ms, t_cmd_lst *cmd_lst)
{
	char	*str;

	str = malloc(sizeof(char) * PATH_MAX + 1);
	if (str == NULL)
		free_builtin(ms, cmd_lst);
	if (getcwd(str, PATH_MAX) == NULL)
	{
		free(str);
		return ;
	}
	ft_printf(1, "%s\n", str);
	free(str);
}
