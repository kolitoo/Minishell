/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:04:32 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/05 15:53:57 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**find_file3(char **split_chevron, t_var *var,
		t_ms *ms, t_cmd_lst *cmd_lst)
{
	if (var->newstr[var->i] == var->c
		&& bool_cote(var->new_variable, var->i) == 1)
	{
		var->newstr = put_space(var->newstr, var->c,
				&var->i, var->new_variable);
		split_chevron[var->k] = malloc(sizeof(char)
				* (len_file(var->newstr, var->i, var->c) + 1));
		if (split_chevron[var->k] == NULL)
			free_file(var, ms, cmd_lst);
		while ((var->newstr[var->i] > ' ' && var->newstr[var->i] != var->c
				&& var->newstr[var->i] != '\0')
			|| bool_cote(var->new_variable, var->i) == 0)
		{
			split_chevron[var->k][var->j] = var->newstr[var->i];
			var->newstr[var->i] = ' ';
			var->i++;
			var->j++;
		}
		split_chevron[var->k][var->j] = '\0';
		split_chevron[var->k] = set_dollar(split_chevron[var->k], &ms, cmd_lst);
		if (var->j == 0)
			split_chevron[var->k] = NULL;
		var->k++;
	}
	return (split_chevron);
}

static char	**find_file2(char **split_chevron, t_var var,
		t_ms *ms, t_cmd_lst *cmd_lst)
{
	var.j = 0;
	var.k = 0;
	var.i = 0;
	while (var.newstr[var.i] != '\0')
	{
		var.j = 0;
		split_chevron = find_file3(split_chevron, &var, ms, cmd_lst);
		if ((var.newstr[var.i] != '\0' && var.newstr[var.i] != var.c)
			|| (var.newstr[var.i] == var.c
				&& bool_cote(var.newstr, var.i) == SUC))
			var.i++;
	}
	split_chevron[var.k] = NULL;
	if (var.k == 0)
		split_chevron = NULL;
	return (split_chevron);
}	

char	**find_file(char *str, char c, t_ms *ms, t_cmd_lst *cmd_lst)
{
	char		**split_chevron;
	char		*str2;
	t_var		var;

	str2 = NULL;
	var.c = c;
	var.newstr = str;
	var.new_variable = str2;
	if (nb_chevron(var.newstr, var.c) == 0)
		return (NULL);
	var.new_variable = strdup(var.newstr);
	if (var.new_variable == NULL)
		free_parsing(ms, cmd_lst, var.newstr);
	split_chevron = malloc(sizeof(char *) * (len_dbl_tab(var.newstr, var.c)));
	if (split_chevron == NULL)
	{
		free(var.new_variable);
		free_parsing(ms, cmd_lst, var.newstr);
	}
	split_chevron = find_file2(split_chevron, var, ms, cmd_lst);
	free(var.new_variable);
	return (split_chevron);
}

void	rights_check(char *str, t_ms **ms, char c)
{
	int	i;

	i = 0;
	if (c == '<')
		(*ms)->limit_mode = NULL;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (i != 0)
			if (rights_check_util(str, &i, ms, c) == 1)
				break ;
		if (str[i] == c && bool_cote(str, i) == ERR)
		{
			if (c == '>')
				(*ms)->boolean_outfile = 1;
			else if (c == '<')
				(*ms)->boolean_infile = 1;
			break ;
		}
		i--;
	}
}

void	right_check_heredoc(char *str, t_ms **ms, t_cmd_lst *cmd_lst)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	var.len = limit_mode_malloc(str);
	(*ms)->limit_mode = malloc(sizeof(int) * var.len);
	if ((*ms)->limit_mode == NULL)
		free_parsing(*ms, cmd_lst, str);
	while (str[var.i] != '\0')
	{
		if (str[var.i] == '<' && str[var.i + 1] == '<')
		{
			(*ms)->limit_mode[var.j] = 2;
			var.j++;
			var.i = var.i + 2;
		}
		if (str[var.i] == '<' && str[var.i + 1] != '<')
		{
			(*ms)->limit_mode[var.j] = 1;
			var.j++;
			var.i++;
		}
		if (str[var.i] != '\0')
			var.i++;
	}
}
