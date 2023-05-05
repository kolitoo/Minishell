/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:29 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/05 14:49:52 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    check_replace(char *str, t_ms *ms, int i, int bool)
{
    int    j;

    j = 0;
    if (bool == 0)
    {
        while (str[j] != '+' && str[j + 1] != '=' && str[j] != '\0')//BOOL 1 POUR = BOOL 0 POUR +=
        {
            if (str[j] != ms->env[i][j])
                break ;
            j++;
        }
        if (str[j + 1] == '=' && (str[j + 1] == ms->env[i][j]))
            return (1);
    }
    else
    {
        while (str[j] != '=' && str[j] != '\0')
        {
            if (str[j] != ms->env[i][j])
                break ;
            j++;
        }
        if (str[j] == '=' && (str[j] == ms->env[i][j]))
            return (1);
    }
    return (0);
}

// int	check_replace(char *str, t_ms *ms, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (str[j] != '=' && str[j] != '\0')
// 	{
// 		if (str[j] != ms->env[i][j])
// 			return (1);
// 		j++;
// 	}
// 	if (str[j] != ms->env[i][j])
// 		return (1);
// 	return (0);
// }

int	check_crt_or_rplc(char *str, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->env[j] != NULL)
	{
		i = 0;
		while (str[i] != '=' && str[i] != '\0')
		{
			if (str[i] != ms->env[j][i])
				break ;
			i++;
		}
		if (str[i] == ms->env[j][i])
			return (0);
		j++;
	}
	return (1);
}

static int    check_forbiden_cara2(char *str, int i, int j)
{
    while (str[i] != '=' && str[i] != '\0')
    {
        if ((str[i] >= 0 && str[i] <= 35) || (str[i] >= 37 && str[i] < 43) || (str[i] > 43 && str[i] <= 47)
            || (str[i] >= 58 && str[i] <= 60) || (str[i] >= 62 && str[i] <= 64)
            || (str[i] >= 91 && str[i] <= 94) || (str[i] == 96)
            || (str[i] >= 123 && str[i] <= 127))
            return (1);
        if ((str[i] >= 48 && str[i] <= 57))
        {
            j = i;
            while (j >= 0)
            {
                if ((str[j] >= 65 && str[j] <= 90)
                    || (str[j] >= 97 && str[j] <= 122))
                    break ;
                j--;
            }
            if (j == -1)
                return (1);
        }
        if ((str[i] == '_') && i == 0 && str[i + 1] == '=')
            return (1);
        i++;
    }
    return (0);
}

// static int	check_forbiden_cara2(char *str, int i, int j)
// {
// 	while (str[i] != '=' && str[i] != '\0')
// 	{
// 		if ((str[i] >= 0 && str[i] <= 35) || (str[i] >= 37 && str[i] <= 47)
// 			|| (str[i] >= 58 && str[i] <= 60) || (str[i] >= 62 && str[i] <= 64)
// 			|| (str[i] >= 91 && str[i] <= 94) || (str[i] == 96)
// 			|| (str[i] >= 123 && str[i] <= 127))
// 			return (1);
// 		if ((str[i] >= 48 && str[i] <= 57))
// 		{
// 			j = i;
// 			while (j >= 0)
// 			{
// 				if ((str[j] >= 65 && str[j] <= 90)
// 					|| (str[j] >= 97 && str[j] <= 122))
// 					break ;
// 				j--;
// 			}
// 			if (j == -1)
// 				return (1);
// 		}
// 		if ((str[i] == '_') && i == 0 && str[i + 1] == '=')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int	check_forbiden_cara(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = 0;
	if (check_forbiden_cara2(str, i, j) == 1)
		return (1);
	return (0);
}

void    export_builtin(t_cmd_lst *cmd_lst, t_ms *ms)
{
    int    i;

    i = 1;
    while (cmd_lst->cmd_option[i] != NULL)
    {
        if (check_forbiden_cara(cmd_lst->cmd_option[i]) == 0)
        {
            if (check_egal(cmd_lst->cmd_option[i]) == 0)
            {
                if ((cmd_lst->cmd_option[1][0] == '+' && cmd_lst->cmd_option[1][1] == '=') || cmd_lst->cmd_option[1][0] == '=')
                    return (ms->builtin_code = 1, (void)0);
                else if (check_add(cmd_lst->cmd_option[i], ms) == 1)
                {
                    printf("concatener\n");
                }
                else if (check_add(cmd_lst->cmd_option[i], ms) == 0)
                {
                    printf("creer\n");
                    (*ms).env = create_env(cmd_lst->cmd_option[i], ms, cmd_lst, 0);
                }
                else if (check_crt_or_rplc(cmd_lst->cmd_option[i], ms) == 1)
                    (*ms).env = create_env(cmd_lst->cmd_option[i], ms, cmd_lst, 1);
                else if (check_crt_or_rplc(cmd_lst->cmd_option[i], ms) == 0)
                    (*ms).env = replac_env(cmd_lst->cmd_option[i], ms, cmd_lst, 1);
            }
            else
                return (ms->builtin_code = 0, (void)0);
        }
        else
            ms->builtin_code = 1;
        i++;
    }
}

// void	export_builtin(t_cmd_lst *cmd_lst, t_ms *ms)
// {
// 	int	i;

// 	i = 1;
// 	while (cmd_lst->cmd_option[i] != NULL)
// 	{
// 		if (check_forbiden_cara(cmd_lst->cmd_option[i]) == 0)
// 		{
// 			if (check_egal(cmd_lst->cmd_option[i]) == 0)
// 			{
// 				if (cmd_lst->cmd_option[1][0] == '=')
// 					return (ms->builtin_code = 1, (void)0);
// 				else if (check_crt_or_rplc(cmd_lst->cmd_option[i], ms) == 1)
// 					(*ms).env = create_env(cmd_lst->cmd_option[i], ms, cmd_lst);
// 				else if (check_crt_or_rplc(cmd_lst->cmd_option[i], ms) == 0)
// 					(*ms).env = replac_env(cmd_lst->cmd_option[i], ms, cmd_lst);
// 			}
// 			else
// 				return (ms->builtin_code = 0, (void)0);
// 		}
// 		else
// 			ms->builtin_code = 1;
// 		i++;
// 	}
// }
