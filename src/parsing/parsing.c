/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:46 by lgirault          #+#    #+#             */
/*   Updated: 2023/04/12 20:34:46 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	launch_check(t_ms *ms)
{
	if (check_fine_cote(ms->line, '\'', '\"') == ERR)
	{
		write(2, "dquote\n", 7);
		return (ERR);
	}
	if (check_space_chevron(ms->line) == ERR)
	{
		write(2, "chevron\n", 8);
		return (ERR);
	}
	if (check_pipe(ms->line) == ERR)
	{
		write(2, "dpipe\n", 7);
		return (ERR);
	}
	return (SUC);
}

t_cmd_lst	*make_cmd_lst(t_ms *ms)
{
	t_cmd_lst	*cmd_lst;
	t_cmd_lst	*temp;
	char	**double_tab;
	int	i;

	i = 1;
	cmd_lst = NULL;
	ms->boolean_infile = 0;
	ms->boolean_outfile = 0;
	if (launch_check(ms) == ERR)
		return (NULL);
	ms->split_pipe = split_incurve(ms->line, '|');
	double_tab = parsing(ms->split_pipe[0], &ms, cmd_lst);
	cmd_lst = lstnew(double_tab, ms);
	while (ms->split_pipe[i] != NULL)
	{
		ms->boolean_infile = 0;
		ms->boolean_outfile = 0;
		double_tab = parsing(ms->split_pipe[i], &ms, cmd_lst);
		temp = lstnew(double_tab, ms);//Proteger si pb
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
			right_check_heredoc(one_cmd, ms);
		else
			rights_check(one_cmd, ms, '<');
		rights_check(one_cmd, ms, '>');
		(*ms)->split_chevron_out = find_file(one_cmd, '>');
		(*ms)->split_chevron_in = find_file(one_cmd, '<');
		one_cmd = strspace_cpy(one_cmd, 0, ms, cmd_lst);
		// if (one_cmd == NULL)
		// 	return (NULL);
	}
	else
	{
		(*ms)->limit_mode = NULL;
		(*ms)->split_chevron_in = NULL;
		(*ms)->split_chevron_out = NULL;
	}
	return (one_cmd);
}

char	**parsing(char    *one_cmd, t_ms **ms, t_cmd_lst *cmd_lst)
{
	char	**double_tab;

	double_tab = NULL;
	if (check_fine_cote(one_cmd, '\'', '\"') == 0)
	{
		one_cmd = strspace_cpy(one_cmd, 0, ms, cmd_lst);
		one_cmd = parsing_chevron(one_cmd, ms, cmd_lst);
		one_cmd = set_dollar(one_cmd, ms, cmd_lst);
		if (nb_cote(one_cmd) == 0)
		{
			double_tab = ft_split(one_cmd, ' ');
			if (!double_tab)
				free_parsing(*ms, cmd_lst, one_cmd);
		}
		else
		{
			double_tab = split_incurve(one_cmd, ' ');
			if (!double_tab)
				free_parsing(*ms, cmd_lst, one_cmd);
		}
		double_tab = clean_str(double_tab);
	}
	else
		write(2, "Probleme cote\n", 15);
	free(one_cmd);
	return (double_tab);
}
