/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:40:04 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 20:37:03 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exit(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "exit") == SUC)
		return (0);
	return (1);
}

void	exit_builtin_pipex(t_cmd_lst *cmd_lst, t_cmd *cmd, t_ms *ms)
{
	if (cmd_lst->limit_mode != NULL)
		if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
			if (unlink("/tmp/.file_temp.txt") == -1)
				error_management(7, cmd);
	clear_lst(&cmd_lst);
	parent(cmd);
	rl_clear_history();
	free(ms->line);
	free_tab(ms->env, 0);
	exit (0);
}

void	exit_builtin_execex(t_cmd_lst *cmd_lst, t_cmd *cmd,
	t_ms *ms, int status)
{
	cmd->wpid = waitpid(cmd->off, &status, 0);
	if (cmd->wpid == -1)
		error_management(8, cmd);
	if (WIFEXITED(status) != 0)
		cmd->exit_status = WEXITSTATUS(status);
	if (cmd_lst->limit_mode != NULL)
		if (cmd_lst->limit_mode[tab_len(cmd_lst->infile_name)] == 2)
			if (unlink("/tmp/.file_temp.txt") == -1)
				error_management(7, cmd);
	clear_lst(&cmd_lst);
	free(ms->line);
	rl_clear_history();
	free_tab(ms->env, 0);
	exit (0);
}
