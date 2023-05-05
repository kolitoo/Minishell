/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:46:46 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/05 16:40:15 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_utils(char *new_variable, char *variable, char *str, int bool)
{
	free(new_variable);
	free(variable);
	if (bool == 1)
		free(str);
}

void	free_env_utils2(char *variable, char *str)
{
	free(variable);
	free(str);
}

void	free_file(t_var *var, t_ms *ms, t_cmd_lst *cmd_lst)
{
	free(var->new_variable);
	free_parsing(ms, cmd_lst, var->newstr);
}
