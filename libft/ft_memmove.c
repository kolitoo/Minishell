/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:19:37 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/23 12:36:55 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*save_dest;
	char	*save_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	save_dest = (char *) dest;
	save_src = (char *) src;
	if (dest > src)
	{
		while (n != 0)
		{
			save_dest[n - 1] = save_src[n - 1];
			n--;
		}
	}
	else
	{
		save_dest = ft_memcpy(dest, src, n);
	}
	return (dest);
}
