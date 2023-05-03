/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:38:56 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/03 11:26:24 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cd(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "cd") == SUC)
		return (0);
	return (1);
}

void	cd_builtin(char **tab, char **envp, t_ms *ms)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	if (tab[2] != NULL)
	{
		return (ms->builtin_code = 1, (void)0);
	}
	if (ft_strcmp(tab[1], "~") == 0)
	{
		while (envp[++var.i] != NULL)
			if (strncmp("HOME=", envp[var.i], 5) == 0)
				break ;
		while (envp[var.i][var.j] != '\0')
			var.j++;
		var.newstr = ft_substr(envp[var.i], 5, ft_strlen(envp[var.i]) - 6);
		if (chdir(var.newstr) != 0)
			return ;
	}
	else if (chdir(tab[1]) != 0)
	{
		ms->builtin_code = 1;
		perror("cd");
		return ;
	}
}
