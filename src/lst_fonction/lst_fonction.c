/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:45:08 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/08 16:32:55 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_lst	*lstnew(char **double_tab, int fd)
{
	t_cmd_lst	*a;

	a = malloc(sizeof(*a));
	if (a == NULL)
		return (NULL);
	a->cmd_option = double_tab;
	a->fd = fd;
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
			free(*cmd_lst);
			(*cmd_lst) = save;
		}
	}
}