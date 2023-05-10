/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:46:46 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/10 16:25:10 by abourdon         ###   ########.fr       */
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

void	free_cd(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
