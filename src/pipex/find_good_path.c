/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_good_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:07:24 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/17 12:18:20 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	last_letter(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i] != '\0' && cmd[i] <= 32)
		i++;
	while (cmd[i] != '\0' && cmd[i] > 32)
	{
		i++;
		j++;
	}
	return (j);
}

int	first_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] <= 32 && cmd[i] != '\0')
		i++;
	return (i);
}

void	exit_free(char **tab_path, char *cmd)
{
	char	*cmd_without_opti;

	cmd_without_opti = ft_substr(cmd, first_space(cmd), last_letter(cmd));
	free_tab(tab_path, 0);
	ft_printf("zsh: command not found: %s\n", cmd_without_opti);
	free(cmd_without_opti);
}

int	check_path(char *cmd, char **tab_path)
{
	if (access(cmd, F_OK | X_OK) == 0)
	{
		free_tab(tab_path, 0);
		return (1);
	}
	return (0);
}

char	*find_good_path(char **envp, char *cmd, t_cmd *cmd1)
{
	char	**tab_path;
	char	*path_cmd;
	int		i;

	i = 0;
	tab_path = make_tab_path(envp, cmd, cmd1);
	if (tab_path == NULL)
		exit(EXIT_FAILURE);
	while (tab_path[i] != NULL)
	{
		path_cmd = ft_strjoin
			(tab_path[i], ft_substr(cmd, first_space(cmd), last_letter(cmd)));
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			free_tab(tab_path, 0);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	exit_free(tab_path, cmd);
	return (NULL);
}
