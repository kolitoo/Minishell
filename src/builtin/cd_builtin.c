/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:38:56 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/30 20:52:45 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cd(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "cd") == SUC)
		return (0);
	return (1);
}

void	cd_builtin(char **tab, char **envp)
{
	char	*home;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strcmp(tab[1], "~") == 0)
	{
		while (envp[i] != NULL)
		{
			if (strncmp("HOME=", envp[i], 5) == 0)
				break ;
			i++;
		}
		while (envp[i][j] != '\0')
			j++;
		home = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 6);
		if (chdir(home) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else if (chdir(tab[1]) != 0)
	{
		perror("cd");
		return ;
	}
}
