/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:38:56 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/04 13:57:38 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	len_newstr(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == 'h' && str[i + 1] == 'o' && str[i + 2] == 'm'
			&& str[i + 3] == 'e' && str[i + 4] == 's' && str[i + 5] == '/')
		{
			i = i + 6;
			while (str[i] != '/')
				i++;
			while (str[i] != '\0')
			{
				len++;
				i++;
			}
			if (str[i] == '\0')
				break ;
		}
	}
	return (len);
}

static void	cd_localise2(t_var *var, char *str)
{
	var->newstr [0] = '~';
	while (str[++var->i])
	{
		if (str[var->i] == 'h' && str[var->i + 1] == 'o'
			&& str[var->i + 2] == 'm' && str[var->i + 3] == 'e'
			&& str[var->i + 4] == 's' && str[var->i + 5] == '/')
		{
			var->i = var->i + 6;
			while (str[var->i] != '/')
				var->i++;
			while (str[var->i] != '\0')
			{
				var->newstr [var->j] = str[var->i];
				var->j++;
				var->i++;
			}
			if (str[var->i] == '\0')
				break ;
		}
	}
	var->newstr[var->j] = '\0';
}

void	cd_localise(t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;
	char	*str;

	var.i = -1;
	var.j = 1;
	str = NULL;
	var.newstr = NULL;
	str = malloc(sizeof(char) * PATH_MAX + 1);
	if (!str)
		free_builtin(ms, cmd_lst);
	getcwd(str, PATH_MAX);
	var.newstr = malloc(sizeof(char) * (len_newstr(str) + 2));
	if (!var.newstr)
	{
		free(str);
		free_builtin(ms, cmd_lst);
	}
	cd_localise2(&var, str);
	free(str);
	ft_printf(1, "%s\n", var.newstr);
	free(var.newstr);
}

int	check_cd(t_cmd_lst *cmd_lst)
{
	if (ft_strcmp(cmd_lst->cmd_option[0], "cd") == SUC)
		return (0);
	return (1);
}

void	cd_builtin(char **tab, char **envp, t_ms *ms)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	if (tab[2] != NULL)
	{
		return (ms->builtin_code = 1, (void)0);
	}
	if (ft_strcmp(tab[1], "~") == 0)
	{
		while (envp[++var.i] != NULL)
			if (strncmp("HOME=", envp[var.i], 5) == 0)
				break ;
		while (envp[var.i][var.j] != '\0')
			var.j++;
		var.newstr = ft_substr(envp[var.i], 5, ft_strlen(envp[var.i]) - 6);
		if (chdir(var.newstr) != 0)
			return ;
	}
	else if (chdir(tab[1]) != 0)
	{
		ms->builtin_code = 1;
		perror("cd");
		return ;
	}
}
