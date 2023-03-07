/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:03 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/21 11:19:08 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t size)
{
	size_t	i;
	char	*array;

	array = (char *) dest;
	i = 0;
	while (i < size)
	{
		array[i] = c;
		i++;
	}
	return (array);
}
