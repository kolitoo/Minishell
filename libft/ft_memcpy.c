/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:00:12 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/23 11:10:49 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_array;
	char	*src_array;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_array = (char *) dest;
	src_array = (char *) src;
	i = 0;
	while (i < n)
	{
		dest_array[i] = src_array[i];
		i++;
	}
	return (dest);
}
