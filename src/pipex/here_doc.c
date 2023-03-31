/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:11:22 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/31 17:39:47 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_prompt(t_cmd *cmd, t_cmd_lst *cmd_lst, int i)
{
	char	*temp;

	while (1)
	{
		temp = get_next_line(0);
		if (temp == NULL)
		{
			free_cmd1(cmd);
			exit(1);
		}
		if (ft_strcmp_n(cmd_lst->infile_name[i], temp) == 0)
			break ;
		if (cmd_lst->cmd_option[0] == NULL && lstsize(cmd_lst) == 1)
			write(cmd->fd_outfile, temp, ft_strlen(temp));
		else
			write(cmd->fd_infile, temp, ft_strlen(temp));
		free(temp);
	}
	free(temp);
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
