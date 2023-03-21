/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:35:47 by lgirault          #+#    #+#             */
/*   Updated: 2022/11/22 13:46:03 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	char	*array;
	size_t	i;

	tab = NULL;
	i = 0;
	if (nmemb * size == 0 || nmemb <= SIZE_MAX / size)
		tab = (void *)malloc(nmemb * size);
	if (tab == NULL)
		return (NULL);
	array = (char *) tab;
	while (i < nmemb * size)
	{
		array[i] = 0;
		i++;
	}
	return (tab);
}
