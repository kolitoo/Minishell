/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:17:26 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 13:36:59 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_malloc(int n)
{
	int				i;
	unsigned int	ret;

	i = 0;
	ret = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		i++;
		ret = n * -1;
	}
	else
		ret = n;
	while (ret >= 1)
	{
		ret = ret / 10;
		i++;
	}
	return (i + 1);
}

static char	*ft_iota2(unsigned int ret, char *str, int i, int neg)
{
	if (ret == 0)
		str[i] = 48;
	while (ret >= 1)
	{
		str[i] = (ret % 10) + 48;
		ret = ret / 10;
		i--;
	}
	if (neg < 0)
		str[i] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	ret;
	char			*str;
	int				neg;

	i = size_malloc(n) - 1;
	ret = 0;
	neg = 1;
	str = malloc(size_malloc(n) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		neg = neg * -1;
		ret = n * -1;
	}
	else
		ret = n;
	str[i] = '\0';
	i--;
	return (ft_iota2(ret, str, i, neg));
}
