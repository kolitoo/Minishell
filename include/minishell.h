/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:51:32 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/10 12:49:44 by lgirault         ###   ########.fr       */
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
	char	*infile_name;
	char	*outfile_name;
	char	*line;
	char	**env;
	char	**split_pipe;
}t_ms;

typedef struct s_cmd_lst
{
	char	*infile_name;
	char	*outfile_name;
	char	**cmd_option;
	struct s_cmd_lst	*next;
}t_cmd_lst;

char	*strspace_cpy(char *str, int i);
char	**parsing(char *one_cmd, t_ms **ms);
char	**split_incurve(char *str, char c);
void	lstadd_back(t_cmd_lst **lst, t_cmd_lst *new);
t_cmd_lst	*lstnew(char **double_tab, char *infile_name, char *outfile_name);
t_cmd_lst	*make_cmd_lst(t_ms *ms);
void	lstclear(t_cmd_lst **cmd_lst);
void	free_tab(char	**tab, int i);
int	nb_cote(char *str);
int	bool_cote(char *str, int i);
int	check_space_chevron(char *str);

#endif