/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:53:27 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/12 20:36:49 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ms		ms;


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
		env[i] = malloc(sizeof(char) * (j + 2));//protect
		j = 0;
		while (envp[i][j] != '\0')
		{
			env[i][j] = envp[i][j];
			j++;
		}
		if (env[i][j - 1] != '\n')
		{
			env[i][j] = '\n';
			j++;
		}
		env[i][j] = '\0';
		j = 0;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	print_map(char **map)
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
		if (map[j] == NULL)
		{
			printf("NULL\n");
		}
		printf("%s\n", map[j]);
		j++;
	}
}

void	print_minishell(void)
{
	ft_printf(1, "\033[32;1m __       __  ______  __    __  ______   ______   __    __  ________  __        __       \n\
/  \\     /  |/      |/  \\  /  |/      | /      \\ /  |  /  |/        |/  |      /  |\n\
$$  \\   /$$ |$$$$$$/ $$  \\ $$ |$$$$$$/ /$$$$$$  |$$ |  $$ |$$$$$$$$/ $$ |      $$ |\n\
$$$  \\ /$$$ |  $$ |  $$$  \\$$ |  $$ |  $$ \\__$$/ $$ |__$$ |$$ |__    $$ |      $$ |\n\
$$$$  /$$$$ |  $$ |  $$$$  $$ |  $$ |  $$      \\ $$    $$ |$$    |   $$ |      $$ |\n\
$$ $$ $$/$$ |  $$ |  $$ $$ $$ |  $$ |   $$$$$$  |$$$$$$$$ |$$$$$/    $$ |      $$ |\n\
$$ |$$$/ $$ | _$$ |_ $$ |$$$$ | _$$ |_ /  \\__$$ |$$ |  $$ |$$ |_____ $$ |_____ $$ |_____\n\
$$ | $/  $$ |/ $$   |$$ | $$$ |/ $$   |$$    $$/ $$ |  $$ |$$       |$$       |$$       |\n\
$$/      $$/ $$$$$$/ $$/   $$/ $$$$$$/  $$$$$$/  $$/   $$/ $$$$$$$$/ $$$$$$$$/ $$$$$$$$/ \n\
\n");
}

void	handler_sigint(int signal)
{
	(void)signal;
	if (ms.here != 1)
	{
		ft_printf(1, "\n");
		ft_printf(1, "\033[36m \033[1m");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (ms.here == 1 && ms.filed == 0)
	{
		//ft_printf(1, "\033[36m \033[1m");
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
		//printf("2\n");
		ms.here = 0;
		ms.sig = 1;
		close(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_lst	*cmd_lst;

	(void)argc;
	(void)argv;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	ms.env = set_env(envp);
	ms.here = 0;
	print_minishell();
	while (1)
	{
		ms.here = 0;
		ft_printf(1, "\033[36m \033[1m");
		ms.line = readline("minishell →  \033[0m");
		if (ms.line == NULL)//CTR + D
			break ;
		ms.sig = 0;
		if (ms.line[0] != '\0')
		{
			cmd_lst = make_cmd_lst(&ms);
			ms.code_erreur1 = ms.code_erreur;
			add_history(ms.line);
			if (cmd_lst != NULL)
			{
				if (lstsize(cmd_lst) > 1)
					ms.code_erreur = pipex(cmd_lst, &ms);
				else if (lstsize(cmd_lst) == 1)
					ms.code_erreur = no_pipe(cmd_lst, &ms);
				else
				{
					free(cmd_lst);
					lstclear(&cmd_lst);
				}
			}
		}
		free(ms.line);
	}
	rl_clear_history();
	free(ms.line);
	free_tab(ms.env, 0);
}

			// 	while (cmd_lst != NULL)
			// 	{
			// 		printf("CMD %d :\n", i);
			// 		print_map(cmd_lst->cmd_option);
			// 		printf("TAB OUTFILE %d :\n", i);
			// 		print_map(cmd_lst->outfile_name);
			// 		printf("TAB INFILE %d :\n", i);
			// 		print_map(cmd_lst->infile_name);
			// 		printf("INFILE MODE : %d\n", cmd_lst->infile_mode);
			// 		printf("OUTFILE MODE : %d\n", cmd_lst->outfile_mode);
			// 		cmd_lst = cmd_lst->next;
			// 		i++;
			// 	}
//pb echo -nnnnnnnnnnnnn -nnnnnnnnnnnnnnnnnnnnnn -nnnnnnnnnnnn
//pb retour ligne heredoc