/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:53:27 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/22 16:18:28 by lgirault         ###   ########.fr       */
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

void	print_minishell(void)
{
		ft_printf("\033[32;1m __       __  ______  __    __  ______   ______   __    __  ________  __        __       \n\
/  \\     /  |/      |/  \\  /  |/      | /      \\ /  |  /  |/        |/  |      /  |\n\
$$  \\   /$$ |$$$$$$/ $$  \\ $$ |$$$$$$/ /$$$$$$  |$$ |  $$ |$$$$$$$$/ $$ |      $$ |\n\
$$$  \\ /$$$ |  $$ |  $$$  \\$$ |  $$ |  $$ \\__$$/ $$ |__$$ |$$ |__    $$ |      $$ |\n\
$$$$  /$$$$ |  $$ |  $$$$  $$ |  $$ |  $$      \\ $$    $$ |$$    |   $$ |      $$ |\n\
$$ $$ $$/$$ |  $$ |  $$ $$ $$ |  $$ |   $$$$$$  |$$$$$$$$ |$$$$$/    $$ |      $$ |\n\
$$ |$$$/ $$ | _$$ |_ $$ |$$$$ | _$$ |_ /  \\__$$ |$$ |  $$ |$$ |_____ $$ |_____ $$ |_____\n\
$$ | $/  $$ |/ $$   |$$ | $$$ |/ $$   |$$    $$/ $$ |  $$ |$$       |$$       |$$       |\n\
$$/      $$/ $$$$$$/ $$/   $$/ $$$$$$/  $$$$$$/  $$/   $$/ $$$$$$$$/ $$$$$$$$/ $$$$$$$$/ \n\n");
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
	print_minishell();
	while (1)
	{
		ft_printf("\033[36m \033[1m");
		ms.line = readline("minishell → \033[0m");
		if (strcmp(ms.line, "exit") == 0)//COMMENTER CAR BUG SUR MAC??//A recoder
			break ;
		if (ms.line[0] != '\0')
		{
			cmd_lst = make_cmd_lst(&ms);
			ms.code_erreur1 = ms.code_erreur;
			add_history(ms.line);
			if (cmd_lst != NULL)
			{
				if (lstsize(cmd_lst) > 1)
					ms.code_erreur = pipex(cmd_lst, ms.env);
				else if (lstsize(cmd_lst) == 1)
					ms.code_erreur = no_pipe(cmd_lst, ms.env);
				// while (cmd_lst != NULL)
				// {
				// 	printf("CMD %d :\n", i);
				// 	print_map(cmd_lst->cmd_option);
				// 	printf("TAB OUTFILE %d :\n", i);
				// 	print_map(cmd_lst->outfile_name);
				// 	printf("TAB INFILE %d :\n", i);
				// 	print_map(cmd_lst->infile_name);
				// 	printf("INFILE MODE : %d\n", cmd_lst->infile_mode);
				// 	printf("OUTFILE MODE : %d\n", cmd_lst->outfile_mode);
					
				// 	cmd_lst = cmd_lst->next;
				// 	i++;
				// }
			}
		}
		i = 0;
		free(ms.line);
	}
	rl_clear_history(); //COMMENTER CAR BUG SUR MAC??
	free(ms.line);
	free_tab(ms.env, 0);
}