/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:35:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/14 10:56:41 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_n(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	int		i;
	char	*newstr;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (str);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (str);
	newstr = malloc(sizeof(char) * 3);
	if (newstr == NULL)
		free_builtin(ms, cmd_lst);
	newstr[0] = '-';
	newstr[1] = 'n';
	newstr[2] = '\0';
	free(str);
	return (newstr);
}

static int	check_e2(char *str)
{
	if (str == NULL)
		return (ERR);
	if (ft_strcmp(str, "-n") == SUC)
		return (ERR);
	if (str[0] != '-')
		return (ERR);
	return (SUC);
}

int	check_e(char *str, int i)
{
	if (check_e2(str) == ERR)
		return (ERR);
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == 'e' || str[i] == 'E')
		{
			i++;
			break ;
		}
		if (str[i] != 'n' && str[i] != 'e' && str[i] != 'E')
			return (ERR);
		i++;
	}
	while (str[i] == 'n' || str[i] == 'e' || str[i] == 'E')
		i++;
	if (str[i] == '\0')
		return (SUC);
	else
		return (ERR);
}

int	check_echo(t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd_lst->cmd_option[0], "echo") == SUC)
	{
		cmd_lst->cmd_option[1] = check_n(cmd_lst->cmd_option[1], ms, cmd_lst);
		if (ft_strcmp(cmd_lst->cmd_option[1], "-n") == SUC
			&& check_e(cmd_lst->cmd_option[1], i) == ERR
			&& check_e(cmd_lst->cmd_option[2], i) == ERR)
		{
			echo_builtin(cmd_lst->cmd_option, 0, cmd_lst, ms);
			return (0);
		}
		else if (check_e(cmd_lst->cmd_option[1], i) == ERR
			&& check_e(cmd_lst->cmd_option[2], i) == ERR)
		{
			echo_builtin(cmd_lst->cmd_option, 1, cmd_lst, ms);
			return (0);
		}
	}
	return (1);
}

void	echo_builtin(char **tab, int bool, t_cmd_lst *cmd_lst, t_ms *ms)
{
	int	j;
	int	i;

	j = 1;
	i = 0;
	while (tab[j] != NULL)
	{
		tab[j] = check_n(tab[j], ms, cmd_lst);
		if (ft_strcmp(tab[j], "-n") != SUC && check_e(tab[j], i) == 1)
		{
			ft_printf(1, "%s", tab[j]);
			if (tab[j + 1] != NULL)
				ft_printf(1, " ");
		}
		j++;
	}
	if (bool == 1)
		ft_printf(1, "\n");
}
