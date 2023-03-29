/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:39:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/29 11:51:06 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_builtin(void)
{
	char	*str;

	str= malloc(sizeof(char) * PATH_MAX + 1);
	getcwd(str, PATH_MAX);
	ft_printf("%s\n", str);
}