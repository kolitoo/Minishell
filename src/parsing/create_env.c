/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:16:17 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/10 16:11:27 by abourdon         ###   ########.fr       */
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

void	solo_export(t_ms *ms, t_cmd_lst *cmd_lst, int i, int j)
{
	char	**print_env;

	print_env = NULL;
	print_env = set_env(ms->env);
	print_env = clean_str(print_env, ms, cmd_lst);
	while (print_env[j] != NULL)
	{
		i = 0;
		ft_printf(1, "declare -x ");
		while (print_env[j][i] != '=')
		{
			ft_printf(1, "%c", print_env[j][i]);
			i++;
			if (print_env[j][i] == '=')
				ft_printf(1, "%c", print_env[j][i]);
		}
		ft_printf(1, "\"");
		i = i + 1;
		while (print_env[j][i] != '\0')
			ft_printf(1, "%c", print_env[j][i++]);
		ft_printf(1, "\"\n");
		j++;
	}
	free_tab(print_env, 0);
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
