/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:25:52 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 16:27:29 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_management(int code_error, t_cmd *cmd)
{
	if (code_error == 2)
		perror("Error launch child procces");
	if (code_error == 3)
		write(2, "Number argument invalid\n", 24);
	if (code_error == 4)
		perror("Error fonction dup2");
	if (code_error == 5)
		perror("Error fonction pipe");
	if (code_error == 6)
		perror ("Error fonction close");
	if (code_error == 7)
		perror ("Error fonction unlink");
	if (code_error == 8)
		perror ("Error fonction waitpid");
	if (code_error != 3)
	{
		free_cmd1(cmd);
		if (cmd->tab_close_outfile != NULL)
			free(cmd->tab_close_outfile);
		if (cmd->tab_close_infile != NULL)
			free(cmd->tab_close_infile);
	}
	exit(EXIT_FAILURE);
}
