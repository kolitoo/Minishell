/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:51:32 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/07 19:03:43 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_ms
{
	char	*line;
	char	**env;
	char	**split_pipe;
}t_ms;

typedef struct s_cmd_lst
{
	int	fd;
	char	**cmd_option;
	struct s_cmd_lst	*next;
}t_cmd_lst;

char	*strspace_cpy(char *str, int i);
char	**parsing(char	*one_pipe);

#endif