/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:47:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/09 10:37:03 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ctrld(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (ms->temp == NULL && ms->sig != 1)
	{
		close_fichier(*cmd, cmd_lst, ms->env);
		close(cmd->fd_infile);
		if (cmd->nbr_cmd > 1)
			close_all(cmd);
		free_cmd1(cmd);
		lstclear(&cmd_lst);
		free_tab(ms->env, 0);
		free(ms->temp);
		exit(1);
	}	
}

static void	ctrlc(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	if (ms->temp == NULL && ms->sig == 1)
	{
		close_fichier(*cmd, cmd_lst, ms->env);
		close(cmd->fd_infile);
		if (cmd->nbr_cmd > 1)
			close_all(cmd);
		free_cmd1(cmd);
		lstclear(&cmd_lst);
		free_tab(ms->env, 0);
		free(ms->temp);
		exit(2);
	}
}

void	read_prompt_condition(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms)
{
	ctrld(cmd, cmd_lst, ms);
	ctrlc(cmd, cmd_lst, ms);
	if (ft_strcmp_n(cmd_lst->infile_name[ms->i_heredoc], ms->temp) == 0)
	{
		close_fichier(*cmd, cmd_lst, ms->env);
		close(cmd->fd_infile);
		if (cmd->nbr_cmd > 1)
			close_all(cmd);
		free_cmd1(cmd);
		lstclear(&cmd_lst);
		free_tab(ms->env, 0);
		free(ms->temp);
		exit (1);
	}
	else
		write(cmd->fd_infile, ms->temp, ft_strlen(ms->temp));
}
