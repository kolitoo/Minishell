/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:53:20 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/21 11:18:28 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*save;

	if (lst != NULL && del != NULL)
	{
		while ((*lst) != NULL)
		{
			save = (*lst)->next;
			ft_lstdelone((*lst), del);
			(*lst) = save;
		}
	}
}
