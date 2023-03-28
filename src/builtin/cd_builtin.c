/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:38:56 by lgirault          #+#    #+#             */
/*   Updated: 2023/03/28 17:04:32 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_builtin(char **tab, char **envp)
{
	char	*home;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strcmp(tab[1], "~") == 0)
	{
		while (envp[i] != NULL)
		{
			if (strncmp("HOME=", envp[i], 5) == 0)
				break;
			i++;
		}
		while (envp[i][j] != '\0')
			j++;
		home = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 6);
		if (chdir(home) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else if (chdir(tab[1]) != 0)
	{
		perror("cd");
		return ;
	}
}