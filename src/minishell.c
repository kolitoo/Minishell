/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:53:27 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/11 16:48:29 by abourdon         ###   ########.fr       */
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

void    print_map(char **map)
{
	int	j;

	j = 0;
	if (map == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (map[j] != NULL)
	{
       		printf("%s\n", map[j]);
		j++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	t_cmd_lst *cmd_lst;
	int	i;
	(void)argc;
	(void)argv;
	ms.env = set_env(envp);
	i = 1;
	while (1)
	{
		ft_printf("\033[36m \033[1m");
		ms.line = readline("minishell → \033[0m");
		// if (strcmp(ms.line, "exit") == 0)//COMMENTER CAR BUG SUR MAC??
		// 	break ;
		if (ms.line[0] != '\0')//Si on appuie sur entree on lance juste une newline
		{
			cmd_lst = make_cmd_lst(&ms);
			add_history(ms.line);
			if (cmd_lst != NULL)
			{
				//envoie a pipex la liste
				while (cmd_lst != NULL)
				{
					printf("CMD %d :\n", i);
					print_map(cmd_lst->cmd_option);
					cmd_lst = cmd_lst->next;
					i++;
				}
				lstclear(&cmd_lst);
			}
		}
		i = 0;
		free(ms.line);
		//Peut etre clear_history
	}
	// rl_clear_history();//COMMENTER CAR BUG SUR MAC??
	free(ms.line);
	free_tab(ms.env, 0);
}