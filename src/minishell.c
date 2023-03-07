/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:53:27 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/07 16:57:39 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**set_env(char	**envp)
{
	int	i;
	int	j;
	char	**env;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		while (envp[i][j] != '\0')
			j++;
		env[i] = malloc(sizeof(char) * (j + 2));
		j = 0;
		while (envp[i][j] != '\0')
		{
			env[i][j] = envp[i][j];
			j++;
		}
		env[i][j] = '\n';
		j++;
		env[i][j] = '\0';
		j = 0;
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	(void)argc;
	(void)argv;
	ms.env = set_env(envp);
	while (1)
	{
		ft_printf("\033[36m \033[1m");
		ms.line = readline("minishell → \033[0m");
		parsing(&ms);
		add_history(ms.line);
		free(ms.line);
		//Peut etre clear_history
	}
	free(ms.line);
}