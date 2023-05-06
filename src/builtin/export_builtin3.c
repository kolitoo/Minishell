/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:53:28 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/06 19:33:18 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int    check_plus(char *str)
{
    int    i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '+' && str[i + 1] == '=')
            return (1);
        i++;
    }
    return (0);
}

int    check_add(char *str, t_ms *ms)
{
    int    i;
    int    j;

    i = 0;
    j = 0;
    if (check_plus(str) == 0)
        return (2);
    while (ms->env[j] != NULL)
    {
        i = 0;
        while (str[i] != '+' && str[i + 1] != '=' && str[i] != '\0')
        {
            if (str[i] != ms->env[j][i])
                break ;
            i++;
        }
        if (str[i + 1] == ms->env[j][i])
            return (1);
        j++;
    }
    return (0);
}

int	pos_plus(char *str)
{
	int	i;

	i = 0;
	while ( str[i] != '\0')
	{
		if (str[i] == '+')
			return (i);
		i++;
	}
	return (0);
}

char	**conca_env(char *str, t_ms *ms, t_cmd_lst *cmd_lst)
{
	int	j;
	char	*straveg;
	char	*strapeg;
	char	*strfinal;
	
	j = 0;
	straveg = ft_substr(str, 0, pos_plus(str) + 1);//protect
	strapeg = ft_substr(str, pos_plus(str) + 2, ft_strlen(str) - pos_plus(str));//protect
	straveg[pos_plus(str)] = '=';
	while (ms->env[j] != NULL)
	{
		if (ft_strncmp(straveg, ms->env[j], pos_egal(ms->env[j])) == 0)
		{
			free(straveg);
			strfinal = join2(ms->env[j], strapeg);//protect
			ms->env = replac_env(strfinal, ms, cmd_lst, 1);
		}
		j++;
	}
	return (ms->env);
}