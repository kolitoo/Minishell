/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:11:22 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 10:36:39 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_prompt(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	//char	*temp;
	int	test;
	ms->here = 1;
	ms->filed = fork();
	if (ms->filed == 0)
	{
		while (ms->sig != 1)
		{
			ms->here = 1;
			ms->temp = readline("> ");
			if (ms->temp == NULL)
			{
				free_cmd1(cmd);
				lstclear(&cmd_lst);
				free_tab(ms->env, 0);
				free(ms->temp);
				exit(2);
			}
			if (ft_strcmp(cmd_lst->infile_name[ms->i_heredoc], ms->temp) == 0)
			{
				free(ms->temp);
				exit (1);
			}
			else
			{
				write(cmd->fd_infile, ms->temp, ft_strlen(ms->temp));
				write(cmd->fd_infile, "\n", 1);
			}
			free(ms->temp);
		}
	}
	waitpid(ms->filed, &test, 0);
	if (test == 512)
	{
		ms->sig = 1;
	}
}

void	init_tab(t_cmd *cmd)
{
	cmd->pipefd = NULL;
	cmd->pid = NULL;
	cmd->cmd = NULL;
	cmd->options = NULL;
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
