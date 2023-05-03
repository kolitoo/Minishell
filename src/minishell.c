/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:53:27 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/03 11:28:00 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ms	g_ms;

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
	if (g_ms.here != 1)
	{
		ft_printf(1, "\n");
		ft_printf(1, "\033[36m \033[1m");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (g_ms.here == 1 && g_ms.filed == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_ms.here = 0;
		g_ms.sig = 1;
		close(0);
	}
}

static void	readline_ok(t_ms *g_ms, t_cmd_lst *cmd_lst)
{
	if (g_ms->line[0] != '\0')
	{
		cmd_lst = make_cmd_lst(g_ms);
		g_ms->code_erreur1 = g_ms->code_erreur;
		add_history(g_ms->line);
		if (cmd_lst != NULL)
		{
			if (lstsize(cmd_lst) > 1)
				g_ms->code_erreur = pipex(cmd_lst, g_ms);
			else if (lstsize(cmd_lst) == 1)
				g_ms->code_erreur = no_pipe(cmd_lst, g_ms);
			else
			{
				free(cmd_lst);
				lstclear(&cmd_lst);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_lst	*cmd_lst;

	(void)argc;
	(void)argv;
	launch_signal();
	cmd_lst = NULL;
	g_ms.env = set_env(envp);
	g_ms.here = 0;
	g_ms.builtin_code = 0;
	//print_minishell();
	while (1)
	{
		g_ms.here = 0;
		ft_printf(1, "\033[36m \033[1m");
		g_ms.line = readline("minishell →  \033[0m");
		if (g_ms.line == NULL)
			break ;
		g_ms.sig = 0;
		readline_ok(&g_ms, cmd_lst);
		// if (g_ms.line[0] != '\0')
		// {
		// 	cmd_lst = make_cmd_lst(&g_ms);
		// 	g_ms.code_erreur1 = g_ms.code_erreur;
		// 	add_history(g_ms.line);
		// 	if (cmd_lst != NULL)
		// 	{
		// 		if (lstsize(cmd_lst) > 1)
		// 			g_ms.code_erreur = pipex(cmd_lst, &g_ms);
		// 		else if (lstsize(cmd_lst) == 1)
		// 			g_ms.code_erreur = no_pipe(cmd_lst, &g_ms);
		// 		else
		// 		{
		// 			free(cmd_lst);
		// 			lstclear(&cmd_lst);
		// 		}
		// 	}
		// }
		free(g_ms.line);
	}
	rl_clear_history();
	if (g_ms.line != NULL)
		free(g_ms.line);
	free_tab(g_ms.env, 0);
}

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
// 	printf("LIMIT MODE %d :\n", i);
// 	printf("%d\n", cmd_lst->limit_mode[0]);
// 	cmd_lst = cmd_lst->next;
// 	i++;
// }

//pb echo -nnnnnnnnnnnnn -nnnnnnnnnnnnnnnnnnnnnn -nnnnnnnnnnnn
//pb retour ligne heredoc