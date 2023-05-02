/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:16:17 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/02 10:59:03 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	**set_env2(char **envp, char **env, int i, int j)
{
	while (envp[i] != NULL)
	{
		while (envp[i][j] != '\0')
			j++;
		env[i] = malloc(sizeof(char) * (j + 2));
		if (env[i] == NULL)
		{
			free_tab(env, 0);
			exit (1);
		}
		j = 0;
		while (envp[i][j] != '\0')
		{
			env[i][j] = envp[i][j];
			j++;
		}
		if (env[i][j - 1] != '\n')
			env[i][j++] = '\n';
		env[i][j] = '\0';
		j = 0;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	**set_env(char	**envp)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		exit (1);
	i = 0;
	env = set_env2(envp, env, i, j);
	return (env);
}

void	solo_export(t_ms *ms, t_cmd_lst *cmd_lst)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	(void)cmd_lst;
	while (ms->env[j] != NULL)
	{
		i = 0;
		ft_printf(1, "declare -x ");
		while (ms->env[j][i] != '=')
		{
			ft_printf(1, "%c", ms->env[j][i]);
			i++;
			if (ms->env[j][i] == '=')
				ft_printf(1, "%c", ms->env[j][i]);
		}
		ft_printf(1, "\"");
		i = i + 1;
		while (ms->env[j][i] != '\n')
			ft_printf(1, "%c", ms->env[j][i++]);
		ft_printf(1, "\"\n");
		j++;
	}
}

void	set_dollar3(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		*i = *i + 1;
		while (str[*i] != '\'')
			*i = *i + 1;
		if (str[*i] == '\'')
			*i = *i + 1;
	}
}