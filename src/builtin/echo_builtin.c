/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:35:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/28 13:58:25 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    printchar(char c)
{
    write(1, &c, 1);
}

void    printstr(char *str)
{
    int    i;

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