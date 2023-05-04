/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:31:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/04 14:01:02 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cpy_env(t_ms *ms, char **new_envp, int *i, t_cmd_lst *cmd_lst)
{
	int	j;

	j = 0;
	while ((*ms).env[*i] != NULL)
	{
		new_envp[*i] = malloc(sizeof(char) * (ft_strlen((*ms).env[*i]) + 1));
		if (new_envp[*i] == NULL)
			free_builtin_export(ms, cmd_lst, new_envp);
		while ((*ms).env[*i][j] != '\0')
		{
			new_envp[*i][j] = (*ms).env[*i][j];
			j++;
		}
		new_envp[*i][j] = '\0';
		j = 0;
		*i = *i + 1;
	}
}

char	**create_env(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_envp = NULL;
	new_envp = malloc(sizeof(char *) * (tab_len((*ms).env) + 3));
	if (new_envp == NULL)
		free_builtin_export(ms, cmd_lst, new_envp);
	cpy_env(ms, new_envp, &i, cmd_lst);
	new_envp[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_envp[i] == NULL)
		free_builtin_export(ms, cmd_lst, new_envp);
	while (str[j] != '\0')
	{
		new_envp[i][j] = str[j];
		j++;
	}
	new_envp[i++][j] = '\0';
	new_envp[i] = NULL;
	free_tab((*ms).env, 0);
	return (new_envp);
}

void	cpy_new_env(char *str, char **new_envp, t_ms *ms, t_cmd_lst *cmd_lst)
{
	new_envp[ms->i_heredoc] = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (new_envp == NULL)
		free_builtin_export(ms, cmd_lst, new_envp);
	while (str[ms->j_heredoc] != '\0')
	{
		new_envp[ms->i_heredoc][ms->j_heredoc] = str[ms->j_heredoc];
		ms->j_heredoc = ms->j_heredoc + 1;
	}
	new_envp[ms->i_heredoc][ms->j_heredoc] = '\0';
	ms->j_heredoc = ms->j_heredoc + 1;
}

void	cpy_old_env(char **new_envp, t_ms *ms, t_cmd_lst *cmd_lst)
{
	new_envp[ms->i_heredoc] = malloc(sizeof(char)
			* (ft_strlen((*ms).env[ms->i_heredoc]) + 1));
	if (new_envp == NULL)
		free_builtin_export(ms, cmd_lst, new_envp);
	while ((*ms).env[ms->i_heredoc][ms->j_heredoc] != '\0')
	{
		new_envp[ms->i_heredoc][ms->j_heredoc]
			= (*ms).env[ms->i_heredoc][ms->j_heredoc];
		ms->j_heredoc = ms->j_heredoc + 1;
	}
}

char	**replac_env(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	char	**new_envp;

	ms->i_heredoc = 0;
	ms->j_heredoc = 0;
	new_envp = NULL;
	(void)cmd_lst;
	new_envp = malloc(sizeof(char *) * (tab_len((*ms).env) + 2));
	if (new_envp == NULL)
		free_builtin_export(ms, cmd_lst, new_envp);
	while ((*ms).env[ms->i_heredoc] != NULL)
	{
		if (check_replace(str, ms, ms->i_heredoc) == 0)
			cpy_new_env(str, new_envp, ms, cmd_lst);
		else
			cpy_old_env(new_envp, ms, cmd_lst);
		new_envp[ms->i_heredoc][ms->j_heredoc] = '\0';
		ms->j_heredoc = 0;
		ms->i_heredoc++;
	}
	new_envp[ms->i_heredoc] = NULL;
	free_tab((*ms).env, 0);
	ms->i_heredoc = 0;
	return (new_envp);
}
