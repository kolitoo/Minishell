/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:31:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 16:28:35 by lgirault         ###   ########.fr       */
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
			free_builtin(ms, cmd_lst, new_envp);
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
		free_builtin(ms, cmd_lst, new_envp);
	cpy_env(ms, new_envp, &i, cmd_lst);
	new_envp[i] = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (new_envp[i] == NULL)
		free_builtin(ms, cmd_lst, new_envp);
	while (str[j] != '\0')
	{
		new_envp[i][j] = str[j];
		j++;
	}
	new_envp[i][j] = '\n';
	j++;
	new_envp[i++][j] = '\0';
	new_envp[i] = NULL;
	free_tab((*ms).env, 0);
	return (new_envp);
}

void	cpy_new_env(char *str, char **new_envp, int *i, int *j)
{
	new_envp[*i] = malloc(sizeof(char) * (ft_strlen(str) + 2));//proteger malloc
	while (str[*j] != '\0')
	{
		new_envp[*i][*j] = str[*j];
		*j = *j + 1;
	}
	new_envp[*i][*j] = '\n';
	*j = *j + 1;
}

void	cpy_old_env(char **new_envp, t_ms *ms, int *i, int *j)
{
	new_envp[*i] = malloc(sizeof(char) * (ft_strlen((*ms).env[*i]) + 1));//proteger malloc
	while ((*ms).env[*i][*j] != '\0')
	{
		new_envp[*i][*j] = (*ms).env[*i][*j];
		*j = *j + 1;
	}
}

char	**replace_env(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_envp = NULL;
	(void)cmd_lst;
	new_envp = malloc(sizeof(char *) * (tab_len((*ms).env) + 2));//proteger malloc
	while ((*ms).env[i] != NULL)
	{
		if (check_replace(str, ms, i) == 0)
			cpy_new_env(str, new_envp, &i, &j);
		else
			cpy_old_env(new_envp, ms, &i, &j);
		new_envp[i][j] = '\0';
		j = 0;
		i++;
	}
	new_envp[i] = NULL;
	free_tab((*ms).env, 0);
	return (new_envp);
}
