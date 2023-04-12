/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:35:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 15:03:21 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *check_n(char *str)
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
    newstr = malloc(sizeof(char) * 3);// proteger
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

int    check_echo(t_cmd_lst *cmd_lst)
{
    if (ft_strcmp(cmd_lst->cmd_option[0], "echo") == SUC)
    {
        cmd_lst->cmd_option[1] = check_n(cmd_lst->cmd_option[1]);
        if (ft_strcmp(cmd_lst->cmd_option[1], "-n") == SUC
            && check_e(cmd_lst->cmd_option[1]) == ERR
            && check_e(cmd_lst->cmd_option[2]) == ERR)
        {
            echo_builtin(cmd_lst->cmd_option, 0);
            return (0);
        }
        else if (check_e(cmd_lst->cmd_option[1]) == ERR
            && check_e(cmd_lst->cmd_option[2]) == ERR)
        {
            echo_builtin(cmd_lst->cmd_option, 1);
            return (0);
        }
        printf("EXECV\n");
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

void    echo_builtin(char **tab, int bool)
{
    int    j;

    j = 1;
    while (tab[j] != NULL)
    {
        tab[j] = check_n(tab[j]);
        if (ft_strcmp(tab[j], "-n") != SUC && check_e(tab[j]) == 1)
        {
            printstr(tab[j]);
            if (tab[j + 1] != NULL)
                printchar(' ');
        }
        j++;
    }
    if (bool == 1)
        printchar('\n');
}