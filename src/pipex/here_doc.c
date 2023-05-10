/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:11:22 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 15:19:21 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_prompt(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	test;

	test = 0;
	ms->here = 1;
	ms->filed = fork();
	signal(SIGINT, handler_sigint);
	if (ms->filed == 0)
	{
		while (ms->sig != 1)
		{
			ms->here = 1;
			ms->temp = readline("> ");
			ms->temp = ft_strjoin(ms->temp, "\n");
			if (ms->temp != NULL)
				ms->temp = set_dollar(ms->temp, &ms, cmd_lst);
			read_prompt_condition(cmd, cmd_lst, ms);
			free(ms->temp);
		}
	}
	waitpid(ms->filed, &test, 0);
	if (test == 512)
	{
		ms->sig = 1;
		ms->builtin_code = 130;
	}
}

void	init_tab(t_cmd *cmd, t_cmd_lst *cmd_lst)
{
	(void)cmd_lst;
	cmd->nbr_cmd = 1;
	cmd->pipefd = NULL;
	cmd->pid = NULL;
	cmd->cmd = NULL;
	cmd->options = NULL;
}

void	init_tab_closefile(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	cmd->tab_close_outfile = NULL;
	cmd->tab_close_infile = NULL;
	if (cmd_lst->outfile_name != NULL)
	{
		cmd->tab_close_outfile = calloc((tab_len(cmd_lst->outfile_name) + 1),
				sizeof(int));
		if (cmd->tab_close_outfile == NULL
			&& tab_len(cmd_lst->outfile_name) + 1 > 0)
			free_cmd(cmd, ms->env, cmd_lst);
	}
	if (cmd_lst->infile_name != NULL)
	{
		cmd->tab_close_infile = ft_calloc((tab_len(cmd_lst->infile_name) + 1),
				sizeof(int));
		if (cmd->tab_close_infile == NULL
			&& tab_len(cmd_lst->outfile_name) + 1 > 0)
		{
			free(cmd->tab_close_outfile);
			free_cmd(cmd, ms->env, cmd_lst);
		}
	}
}

void	close_fd(t_cmd *cmd)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
		if (close(cmd->fd_infile) == -1)
			error_management(6, cmd);
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 0)
		if (close(cmd->fd_outfile) == -1)
			error_management(6, cmd);
}

int	where(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
