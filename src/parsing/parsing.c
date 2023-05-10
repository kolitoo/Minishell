/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 13:08:58 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	launch_check(t_ms *ms, t_cmd_lst *cmd_lst)
{
	ms->boolean_infile = 0;
	ms->boolean_outfile = 0;
	if (check_fine_cote(ms->line, '\'', '\"') == ERR)
	{
		write(2, "Syntax Error: near unexpected token quote\n", 42);
		ms->code_erreur = 1;
		return (ERR);
	}
	if (check_space_chevron(ms->line, ms, cmd_lst) == ERR)
	{
		write(2, "syntax error near unexpected token '>'\n", 39);
		ms->code_erreur = 1;
		return (ERR);
	}
	if (check_pipe(ms->line, 0) == ERR)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		ms->code_erreur = 1;
		return (ERR);
	}
	return (SUC);
}

t_cmd_lst	*make_cmd_lst(t_ms *ms)
{
	t_cmd_lst	*cmd_lst;
	t_cmd_lst	*temp;
	char		**double_tab;
	int			i;

	i = 1;
	cmd_lst = NULL;
	if (launch_check(ms, cmd_lst) == ERR)
		return (NULL);
	ms->split_pipe = split_incurve(ms->line, '|', ms, cmd_lst);
	double_tab = parsing(ms->split_pipe[0], &ms, cmd_lst);
	cmd_lst = lstnew(double_tab, ms);
	while (ms->split_pipe[i] != NULL)
	{
		ms->boolean_infile = 0;
		ms->boolean_outfile = 0;
		double_tab = parsing(ms->split_pipe[i], &ms, cmd_lst);
		temp = lstnew(double_tab, ms);
		if (temp == NULL)
			free_make_cmd_lst(ms, cmd_lst, double_tab);
		lstadd_back(&cmd_lst, temp);
		i++;
	}
	free(ms->split_pipe);
	return (cmd_lst);
}

char	*parsing_chevron(char *one_cmd, t_ms **ms, t_cmd_lst *cmd_lst)
{
	if (exist_chevron(one_cmd) == SUC)
	{
		if (her_doc_check(one_cmd) == SUC)
			right_check_heredoc(one_cmd, ms, cmd_lst);
		else
			rights_check(one_cmd, ms, '<');
		rights_check(one_cmd, ms, '>');
		(*ms)->split_chevron_out = find_file(one_cmd, '>', *ms, cmd_lst);
		(*ms)->split_chevron_in = find_file(one_cmd, '<', *ms, cmd_lst);
		if ((*ms)->split_chevron_out != NULL)
			(*ms)->split_chevron_out = clean_str((*ms)->split_chevron_out,
					*ms, cmd_lst);
		if ((*ms)->split_chevron_in != NULL)
			(*ms)->split_chevron_in = clean_str((*ms)->split_chevron_in,
					*ms, cmd_lst);
		one_cmd = strspace_cpy(one_cmd, 0, ms, cmd_lst);
	}
	else
	{
		(*ms)->limit_mode = NULL;
		(*ms)->split_chevron_in = NULL;
		(*ms)->split_chevron_out = NULL;
	}
	return (one_cmd);
}

static char	*make_one_cmd(char *one_cmd, t_ms **ms, t_cmd_lst *cmd_lst)
{
	one_cmd = strspace_cpy(one_cmd, 0, ms, cmd_lst);
	one_cmd = parsing_chevron(one_cmd, ms, cmd_lst);
	one_cmd = set_dollar(one_cmd, ms, cmd_lst);
	return (one_cmd);
}

char	**parsing(char *one_cmd, t_ms **ms, t_cmd_lst *cmd_lst)
{
	char	**double_tab;

	double_tab = NULL;
	one_cmd = make_one_cmd(one_cmd, ms, cmd_lst);
	if (nb_cote(one_cmd) == 0)
	{
		double_tab = ft_split(one_cmd, ' ');
		if (!double_tab)
			free_parsing(*ms, cmd_lst, one_cmd);
	}
	else
	{
		double_tab = split_incurv3(one_cmd, ' ', *ms, cmd_lst);
		if (!double_tab)
			free_parsing(*ms, cmd_lst, one_cmd);
	}
	if (ft_strcmp(double_tab[0], "export") != 0)
		double_tab = clean_str(double_tab, *ms, cmd_lst);
	free(one_cmd);
	return (double_tab);
}
