/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:29 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/30 13:58:12 by lgirault         ###   ########.fr       */
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

int	check_replace(char *str, t_ms *ms, int i)
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
		if (check_replace(str, ms, i) == 0)
		{
			new_envp[i] = malloc(sizeof(char) * (ft_strlen(str) + 2));
			while (str[j] != '\0')
			{
				new_envp[i][j] = str[j];
				j++;
			}
			new_envp[i][j] = '\n';
			j++;
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

int	check_create_or_replace(char *str, t_ms *ms)
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

int	check_forbiden_cara(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0' || i == 0)
		return (1);
	i = 0;
	while (str[i] != '=')
	{
		if ((str[i] >= 0 && str[i] <= 35) || (str[i] >= 37 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 60) || (str[i] >= 62 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 94) || (str[i] == 96) || (str[i] >= 123 && str[i] <= 127))
			return (1);
		if ((str[i] >= 48 && str[i] <= 57))
		{
			j = i;
			while (j >= 0)
			{
				if ((str[j] >= 65 && str[j] <= 90) || (str[j] >= 97 && str[j] <= 122))
					break ;
				j--;
			}
			if (j == -1)
				return (1);
		}
		if ((str[i] == '_') && i == 0 && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_builtin(t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	i;

	i = 1;
	while (cmd_lst->cmd_option[i] != NULL)
	{
		if (check_forbiden_cara(cmd_lst->cmd_option[i]) == 0)
		{
			if (check_create_or_replace(cmd_lst->cmd_option[i], ms) == 1)
				(*ms).env = create_env(cmd_lst->cmd_option[i], ms);
			else if (check_create_or_replace(cmd_lst->cmd_option[i], ms) == 0)
				(*ms).env = replace_env(cmd_lst->cmd_option[i], ms);
		}
		else
			ft_printf("export: not an identifier: %s\n", cmd_lst->cmd_option[i]);
		i++;
	}
}