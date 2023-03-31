/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cote2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:48:12 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/31 17:26:35 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_cotev2(char *str, int i, char c)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j <= i)
	{
		if (str[j] == c)
			k++;
		j++;
	}
	if ((k % 2) == 0) //pas entre cote
		return (ERR);
	return (SUC);
}

int	bool_cotev2(char *str, int i)
{
	int	one;
	int	two;

	one = valid_cotev2(str, i, '\'');
	two = valid_cotev2(str, i, '\"');
	if (one == ERR && two == SUC) //entre cote
		return (SUC);
	if (one == SUC && two == ERR) //entre cote
		return (SUC);
	if (one == SUC && two == SUC) //entre cote
		return (SUC);
	if (one == ERR && two == ERR) //pas entre cote
		return (ERR);
	return (ERR);
}

static    void    clear_quote2(char *str, int i, int *len)
{
    while (str[i] != '\0')
    {
        if (str[i] == '\"')
        {
            while (str[++i] != '\"')
                *len = *len + 1;
            if (str[i] == '\"')
                i++;
        }
        if (str[i] == '\'')
        {
            while (str[++i] != '\'')
		*len = *len + 1;
            if (str[i] == '\'')
                i++;
        }
        if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
        {
            *len = *len + 1;
            i++;
        }
    }
}

static char    *clear_quote3(char *str, char *newstr, int i, int j)
{
    while (str[i] != '\0')
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
                newstr[j++] = str[i++];
            if (str[i] == '\"')
                i++;
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
                newstr[j++] = str[i++];
            if (str[i] == '\'')
                i++;
        }
        if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
            newstr[j++] = str[i++];
    }
    newstr[j] = '\0';
    return (newstr);
}

char    *clear_quote(char *str)
{
    int        i;
    int        j;
    int        len;
    char    *newstr;

    i = 0;
    j = 0;
    len = 0;
    clear_quote2(str, i, &len);
    newstr = malloc(sizeof(char) * (len + 1)); // protect malloc
    i = 0;
    newstr = clear_quote3(str, newstr, i, j);
    free(str);
    return (newstr);
}

// char    *clear_quote(char    *str)
// {
//     int    i;
//     int    j;
//     int    len;
//     char    *newstr;

//     i = 0;
//     j = 0;
//     len = 0;
//     while (str[i] != '\0')
//     {
//         if (str[i] == '\"')
//         {
//             i++;
//             while (str[i] != '\"')
//             {
//                 len++;
//                 i++;
//             }
//             if (str[i] == '\"')
//                 i++;
//         }
//         if (str[i] == '\'')
//         {
//             i++;
//             while (str[i] != '\'')
//             {
//                 len++;
//                 i++;
//             }
//             if (str[i] == '\'')
//                 i++;
//         }
//         if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
//         {
//             len++;
//             i++;
//         }
//     }
//     i = 0;
//     newstr = malloc(sizeof(char) * (len + 1));
//     while (str[i] != '\0')
//     {
//         if (str[i] == '\"')
//         {
//             i++;
//             while (str[i] != '\"')
//             {
//                 newstr[j] = str[i];
//                 i++;
//                 j++;
//             }
//             if (str[i] == '\"')
//                 i++;
//         }
//         if (str[i] == '\'')
//         {
//             i++;
//             while (str[i] != '\'')
//             {
//                 newstr[j] = str[i];
//                 i++;
//                 j++;
//             }
//             if (str[i] == '\'')
//                 i++;
//         }
//         if (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
//         {
//             newstr[j] = str[i];
//             i++;
//             j++;
//         }
//     }
//     newstr[j] = '\0';
//     free(str);
//     return (newstr);
// }
