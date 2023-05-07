/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:06:11 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 13:08:24 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i - 1);
}

void	variable_util(t_var *var, char *str)
{
	if (str[var->k] == '$')
		var->k++;
	while ((str[var->k] >= 'a' && str[var->k] <= 'z')
		|| (str[var->k] >= 'A' && str[var->k] <= 'Z'))
		var->k++;
	while (str[var->k] != '\0')
		var->newstr[var->i++] = str[var->k++];
	var->newstr[var->i] = '\0';
}

int	check_if_unset(char *str, t_ms *ms)
{
	int		i;
	int		j;
	char	*s1;

	i = 0;
	j = 0;
	while (ms->env[i] != NULL)
	{
		s1 = ft_substr(ms->env[i], 0, pos_egal(ms->env[i]));
		if (ft_strcmp(s1, str) == 0)
		{
			free (s1);
			return (0);
		}
		i++;
		free (s1);
	}
	return (1);
}

int	check_cd(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "cd") == SUC)
	{
		if (cmd_lst->cmd_option[1] != NULL && cmd_lst->cmd_option[2] != NULL)
			ft_printf(2, "cd : too many arguments\n");
		return (0);
	}
	return (1);
}

char	*join2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlenn(s1) + ft_strlenn(s2) + 1));
	if (!str)
		return (free(s2), NULL);
	while (s1[++i] != '\0')
	{
		str[j++] = s1[i];
	}
	i = -1;
	while (s2[++i] != '\0')
	{
		str[j++] = s2[i];
	}
	str[j] = '\0';
	free (s2);
	return (str);
}
