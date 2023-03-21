/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:45:08 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/20 14:51:39 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_lst	*lstnew(char **double_tab, t_ms *ms)
{
	t_cmd_lst	*a;

	a = malloc(sizeof(*a));
	if (a == NULL)
		return (NULL);
	a->cmd_option = double_tab;
	a->outfile_mode = ms->boolean_outfile;
	a->infile_mode = ms->boolean_infile;
	a->infile_name = ms->split_chevron_in;
	a->outfile_name = ms->split_chevron_out;
	a->next = NULL;
	return (a);
}

void	lstadd_back(t_cmd_lst **lst, t_cmd_lst *new)
{
	t_cmd_lst	*ptr;

	ptr = *lst;
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

void	lstclear(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*save;

	if (cmd_lst != NULL)
	{
		while ((*cmd_lst) != NULL)
		{
			save = (*cmd_lst)->next;
			free_tab((*cmd_lst)->cmd_option, 0);
			if ((*cmd_lst)->infile_name != NULL)
				// free((*cmd_lst)->infile_name);
				free_tab((*cmd_lst)->infile_name, 0);// verif si bon
			// if ((*cmd_lst)->outfile_name != NULL)
			// free((*cmd_lst)->outfile_name);
			free_tab((*cmd_lst)->outfile_name, 0);// verif si bon
			free(*cmd_lst);
			(*cmd_lst) = save;
		}
	}
}

int	lstsize(t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst != NULL)
	{
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (i);
}