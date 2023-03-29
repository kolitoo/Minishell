/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:29 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/29 17:32:52 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_env(char *str, t_ms *ms)
{
	char	**new_envp;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * (tab_len((*ms).env) + 3));
	while ((*ms).env[i] != NULL)
	{
		new_envp[i] = malloc(sizeof(char) * (ft_strlen((*ms).env[i]) + 1));
		while ((*ms).env[i][j] != '\0')
		{
			new_envp[i][j] = (*ms).env[i][j];
			j++;
		}
		new_envp[i][j] = '\0';
		j = 0;
		i++;
	}
	new_envp[i] = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[j] != '\0')
	{
		new_envp[i][j] = str[j];
		j++;
	}
	new_envp[i][j] = '\n';
	j++;
	new_envp[i][j] = '\0';
	i++;
	new_envp[i] = NULL;
	free_tab((*ms).env, 0);
	return (new_envp);
}

int	test(char *str, t_ms *ms, int i)
{
	int	j;

	j = 0;
	while (str[j] != '=' && str[j] != '\0')
	{
		if (str[j] != ms->env[i][j])
			return (1);
		j++;
	}
	if (str[j] != ms->env[i][j])
		return (1);
	return (0);
}

char	**replace_env(char *str, t_ms *ms)
{
	char	**new_envp;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * (tab_len((*ms).env) + 2));
	while ((*ms).env[i] != NULL)
	{
		if (test(str, ms, i) == 0)
		{
			new_envp[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
			while (str[j] != '\0')
			{
				new_envp[i][j] = str[j];
				j++;
			}
		}
		else
		{
			new_envp[i] = malloc(sizeof(char) * (ft_strlen((*ms).env[i]) + 1));
			while ((*ms).env[i][j] != '\0')
			{
				new_envp[i][j] = (*ms).env[i][j];
				j++;
			}
		}
			new_envp[i][j] = '\0';
			j = 0;
			i++;
	}
	new_envp[i] = NULL;
	free_tab((*ms).env, 0);
	return (new_envp);
}

int	test2(char *str, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->env[j] != NULL)
	{
		i = 0;
		while (str[i] != '=' && str[i] != '\0')
		{
			if (str[i] != ms->env[j][i])
				break ;
			i++;
		}
		if (str[i] == ms->env[j][i])
			return (0);
		j++;
	}
	return (1);
}

char	**export_builtin(t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_lst->cmd_option[i] != NULL)
	{
		j = 0;
		while (cmd_lst->cmd_option[i][j] != '\0')
		{
			if (cmd_lst->cmd_option[i][j] == '=' && j != 0 && test2(cmd_lst->cmd_option[i], ms) == 1)
				(*ms).env = create_env(cmd_lst->cmd_option[i], ms);
			else if (cmd_lst->cmd_option[i][j] == '=' && j != 0 && test2(cmd_lst->cmd_option[i], ms) == 0)
				(*ms).env = replace_env(cmd_lst->cmd_option[i], ms);
			j++;
		}
		i++;
	}
	return ((*ms).env);
}