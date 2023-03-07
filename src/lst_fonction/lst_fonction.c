/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:45:08 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/07 19:47:07 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_lst	*lstnew(char **double_tab, int fd)
{
	t_cmd_lst	*a;
	int	i;
	int	j;

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