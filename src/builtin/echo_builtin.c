/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:35:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/01 19:37:47 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_echo(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "echo") == SUC)
	{
		if (ft_strcmp(cmd_lst->cmd_option[1], "-n") == SUC
			&& ft_strcmp(cmd_lst->cmd_option[2], "-e") != 0
			&& ft_strcmp(cmd_lst->cmd_option[2], "-E") != 0)
		{
			echo_builtin(cmd_lst->cmd_option, 1);
			return (0);
		}
		else if (ft_strcmp(cmd_lst->cmd_option[1], "-e") != 0
			&& ft_strcmp(cmd_lst->cmd_option[1], "-E") != 0
			&& ft_strcmp(cmd_lst->cmd_option[2], "-e") != 0
			&& ft_strcmp(cmd_lst->cmd_option[2], "-E") != 0)
		{
			echo_builtin(cmd_lst->cmd_option, 0);
			return (0);
		}
	}
	return (1);
}

void	printchar(char c)
{
	write(1, &c, 1);
}

void	printstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printchar(str[i]);
		i++;
	}
}

void	echo_builtin(char **tab, int bool)
{
	int	j;

	j = 0;
	if (bool == 0)
		j = 1;
	else if (bool == 1)
		j = 2;
	while (tab[j] != NULL)
	{
		printstr(tab[j]);
		if (tab[j + 1] != NULL)
			printchar(' ');
		j++;
	}
	if (bool == 0)
		printchar('\n');
}
