/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tab_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:22:27 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/09 09:44:35 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_colon(char *path_line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (path_line == NULL)
		return (0);
	while (path_line[i] != '\0')
	{
		if (path_line[i] == ':')
			count++;
		i++;
	}
	return (count + 1);
}
/*+1 car dernier chemin d'acces n'a pas de ':'*/

char	*make_str_path_2(char **envp, t_tab ijk)
{
	char	*str;
	int		size;
	int		size_colon;

	size = ft_strlen(envp[ijk.j]);
	size_colon = nb_colon(envp[ijk.j]);
	if (size == 0 && size_colon == 0)
		exit(EXIT_FAILURE);
	str = malloc(sizeof(char) * size + size_colon - 4);
	if (str == NULL)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	while (envp[ijk.j][ijk.i] != '/')
		ijk.i++;
	while (envp[ijk.j][ijk.i] != '\0')
	{
		if (envp[ijk.j][ijk.i] == ':')
			str[ijk.k++] = '/';
		str[ijk.k++] = envp[ijk.j][ijk.i++];
	}
	str[ijk.k++] = '/';
	str[ijk.k] = '\0';
	return (str);
}

void	find_path(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst)
{
	char	*cmd_without_opti;

	cmd->options = cmd_lst->cmd_option;
	if (cmd->options[0] == NULL)
		return ;
	if (where(cmd->options[0]) == 1)
	{
		if (access(cmd_lst->cmd_option[0], F_OK | X_OK) == 0)
			cmd->cmd = ft_strdup(cmd_lst->cmd_option[0]);
		else
		{
			cmd_without_opti = ft_strdup(cmd_lst->cmd_option[0]);
			ft_printf(2, "zsh: command not found: %s\n", cmd_without_opti);
			free(cmd_without_opti);
		}
	}
	else
		cmd->cmd = find_good_path(envp, cmd_lst->cmd_option[0], cmd);
}

char	*make_str_path(char **envp, char *cmd, t_cmd *cmd1)
{
	t_tab	ijk;

	ijk.j = 0;
	ijk.i = 0;
	ijk.k = 0;
	while (envp[ijk.j] != NULL)
	{
		if (ft_strncmp(envp[ijk.j], "PATH=", 5) == 0)
			break ;
		ijk.j++;
	}
	if (envp[ijk.j] == NULL)
	{
		ft_printf(2, "zsh: command not found: %s\n", cmd);
		free_cmd1(cmd1);
		if (cmd1->tab_close_outfile != NULL)
			free(cmd1->tab_close_outfile);
		if (cmd1->tab_close_infile != NULL)
			free(cmd1->tab_close_infile);
		exit(127);
	}
	return (make_str_path_2(envp, ijk));
}

char	**make_tab_path(char **envp, char *cmd, t_cmd *cmd1)
{
	char	*str_path;
	char	**split_path;

	str_path = make_str_path(envp, cmd, cmd1);
	split_path = ft_split2(str_path, ':');
	free(str_path);
	return (split_path);
}
