/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:35:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/13 17:10:38 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	printchar(char c)
// {
// 	write(1, &c, 1);
// }

// void	printstr(char *str)
// {
// 	int	i;
// 	i = 0;
// 	while (str[i])
// 	{
// 		printchar(str[i]);
// 		i++;
// 	}
// }

// int	check_echo(t_cmd_lst *cmd_lst, t_ms *ms)
// {
// 	(void)ms;
// 	if (ft_strcmp(cmd_lst->cmd_option[0], "echo") == SUC)
// 	{
// 		if (ft_strcmp(cmd_lst->cmd_option[1], "-n") == SUC
// 			&& ft_strcmp(cmd_lst->cmd_option[2], "-e") != 0
// 			&& ft_strcmp(cmd_lst->cmd_option[2], "-E") != 0)
// 		{
// 			echo_builtin(cmd_lst->cmd_option, 1);
// 			return (0);
// 		}
// 		else if (ft_strcmp(cmd_lst->cmd_option[1], "-e") != 0
// 			&& ft_strcmp(cmd_lst->cmd_option[1], "-E") != 0
// 			&& ft_strcmp(cmd_lst->cmd_option[2], "-e") != 0
// 			&& ft_strcmp(cmd_lst->cmd_option[2], "-E") != 0)
// 		{
// 			echo_builtin(cmd_lst->cmd_option, 0);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// void	echo_builtin(char **tab, int bool)
// {
// 	int	j;

// 	j = 0;
// 	if (bool == 0)
// 		j = 1;
// 	else if (bool == 1)
// 		j = 2;
// 	while (tab[j] != NULL)
// 	{
// 		ft_printf(1, "%s", tab[j]);
// 		if (tab[j + 1] != NULL)
// 			ft_printf(1, " ");
// 		j++;
// 	}
// 	if (bool == 0)
// 		ft_printf(1, "\n");
// }

char    *check_n(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
    int    i;
    char    *newstr;

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

int    check_e(char *str)
{
    int    i;
    
    i = 0;
    if (str == NULL)
        return (ERR);
    if (ft_strcmp(str, "-n") == SUC)
        return (ERR);
    if (str[0] == '-')
        i++;
    else if (str[0] != '-')
        return (ERR);
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

int    check_echo(t_cmd_lst *cmd_lst, t_ms *ms)
{
    if (ft_strcmp(cmd_lst->cmd_option[0], "echo") == SUC)
    {
        cmd_lst->cmd_option[1] = check_n(cmd_lst->cmd_option[1], ms, cmd_lst);
        if (ft_strcmp(cmd_lst->cmd_option[1], "-n") == SUC
            && check_e(cmd_lst->cmd_option[1]) == ERR
            && check_e(cmd_lst->cmd_option[2]) == ERR)
        {
            echo_builtin(cmd_lst->cmd_option, 0, cmd_lst, ms);
            return (0);
        }
        else if (check_e(cmd_lst->cmd_option[1]) == ERR
            && check_e(cmd_lst->cmd_option[2]) == ERR)
        {
            echo_builtin(cmd_lst->cmd_option, 1, cmd_lst, ms);
            return (0);
        }
    }
    return (1);
}

// void	printchar(char c, t_cmd *cmd)
// {
// 	write(cmd->fd_outfile, &c, 1);
// }

// void	printstr(char *str, t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printchar(str[i], cmd);
// 		i++;
// 	}
// }

void    echo_builtin(char **tab, int bool, t_cmd_lst *cmd_lst, t_ms *ms)
{
    int    j;

    j = 1;
    while (tab[j] != NULL)
    {
        tab[j] = check_n(tab[j], ms, cmd_lst);
        if (ft_strcmp(tab[j], "-n") != SUC && check_e(tab[j]) == 1)
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