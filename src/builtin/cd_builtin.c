/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:38:56 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 16:24:50 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_localise2(t_ms *ms, t_cmd_lst *cmd_lst, t_var var)
{
	var.newstr = malloc(sizeof(char) * PATH_MAX + 1);
	if (!var.newstr)
		free_builtin(ms, cmd_lst);
	getcwd(var.newstr, PATH_MAX + 1);
	var.newstr = join2("OLDPWD=", var.newstr);
	if (var.newstr == NULL)
		free_builtin(ms, cmd_lst);
	var.new_variable = ft_substr(ms->env[var.j],
			pos_egal(ms->env[var.j]) + 1,
			ft_strlen(ms->env[var.j]) - (pos_egal(ms->env[var.j]) + 1));
	if (var.new_variable == NULL)
		return (free(var.newstr), free_builtin(ms, cmd_lst), (void)0);
	if (chdir(var.new_variable) != 0)
		return (free(var.new_variable), free(var.newstr), (void)0);
	ms->env = replac_env(var.newstr, ms, cmd_lst, 1);
	free(var.new_variable);
	free(var.newstr);
}

void	cd_localise(t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.j = 0;
	while (ms->env[var.j] != NULL)
	{
		if (ft_strncmp("OLDPWD=", ms->env[var.j],
				pos_egal(ms->env[var.j])) == 0)
		{
			cd_localise2(ms, cmd_lst, var);
			break ;
		}
		var.j++;
		if (ms->env[var.j] == NULL)
		{
			ft_printf(2, "OLDPWD not set\n");
			break ;
		}
	}
}

void	cd_alone(char **envp, t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	var.new_variable = malloc(sizeof(char) * PATH_MAX + 1);
	if (!var.new_variable)
		free_builtin(ms, cmd_lst);
	while (envp[++var.i] != NULL)
		if (strncmp("HOME=", envp[var.i], 5) == 0)
			break ;
	while (envp[var.i][var.j] != '\0')
		var.j++;
	var.newstr = ft_substr(envp[var.i], 5, ft_strlen(envp[var.i]) - 5);
	if (var.newstr == NULL)
		return (free_builtin(ms, cmd_lst), free(var.new_variable), (void)0);
	if (getcwd(var.new_variable, PATH_MAX + 1) != NULL)
	{
		var.new_variable = join2("OLDPWD=", var.new_variable);
		if (var.new_variable == NULL)
			return (free_builtin(ms, cmd_lst), free(var.newstr), (void)0);
		ms->env = replac_env(var.new_variable, ms, cmd_lst, 1);
	}
	if (chdir(var.newstr) != 0)
		return (free(var.new_variable), free(var.newstr), (void)0);
	free_cd(var.new_variable, var.newstr);
}

void	cd_builtin2(char **tab, t_ms *ms, t_cmd_lst *cmd_lst, t_var var)
{
	if (ft_strcmp(tab[1], "~") == 0)
	{
		while (ms->env[++var.i] != NULL)
			if (strncmp("HOME=", ms->env[var.i], 5) == 0)
				break ;
		var.newstr = ft_substr(ms->env[var.i], 5,
				ft_strlen(ms->env[var.i]) - 5);
		if (var.newstr == NULL)
			return (free_builtin(ms, cmd_lst), free(var.new_variable), (void)0);
		if (chdir(var.newstr) != 0)
			return (free(var.new_variable), free(var.newstr), (void)0);
		free(var.newstr);
	}
	else if (chdir(tab[1]) != 0)
	{
		ms->builtin_code = 1;
		perror("cd");
	}
}

void	cd_builtin(char **tab, t_ms *ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.i = -1;
	var.j = 0;
	if (tab[2] != NULL)
		return (ms->builtin_code = 1, (void)0);
	var.new_variable = malloc(sizeof(char) * PATH_MAX + 1);
	if (!var.new_variable)
		free_builtin(ms, cmd_lst);
	if (getcwd(var.new_variable, PATH_MAX + 1) != NULL)
	{
		var.new_variable = join2("OLDPWD=", var.new_variable);
		if (var.new_variable == NULL)
			free_builtin(ms, cmd_lst);
		ms->env = replac_env(var.new_variable, ms, cmd_lst, 1);
	}
	cd_builtin2(tab, ms, cmd_lst, var);
	return (free(var.new_variable), (void)0);
}
