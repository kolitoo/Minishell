/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:51:32 by abourdon          #+#    #+#             */
/*   Updated: 2023/03/15 23:05:12 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR 1
# define SUC 0

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_ms
{
	char	*line;
	char	**env;
	char	**split_pipe;
	char	**split_chevron_in;
	char	**split_chevron_out;
	int	boolean_outfile;
	int	boolean_infile;
}t_ms;

typedef struct s_cmd_lst
{
	int				infile_mode;
	int				outfile_mode;
	char				**infile_name;
	char				**outfile_name;
	char				**cmd_option;
	struct s_cmd_lst	*next;
}t_cmd_lst;

int			nb_cote(char *str);
int			check_space_chevron(char *str);
int			bool_cote(char *str, int i);
int			nb_chevron(char *str, char c);
char		*strspace_cpy(char *str, int i);
char		**parsing(char *one_cmd, t_ms **ms);
char		**split_incurve(char *str, char c);
void		lstadd_back(t_cmd_lst **lst, t_cmd_lst *new);
void		lstclear(t_cmd_lst **cmd_lst);
void		free_tab(char	**tab, int i);
void		rights_check(char *str, t_ms **ms, char c);
t_cmd_lst	*make_cmd_lst(t_ms *ms);
int	check_fine_cote(char *line, char c, char cote);
int	check_cote(char *line, char c);
t_cmd_lst	*lstnew(char **double_tab, t_ms *ms);
void    print_map(char **map);
char	**find_file(char *str, char c);

#endif