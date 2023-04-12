/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:51:32 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/12 10:22:29 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX

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
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/wait.h>
# include <limits.h>
#include <signal.h>


typedef struct s_tab
{
	int	i;
	int	j;
	int	k;
}	t_tab;

typedef struct s_var
{
	int	i;
	int	j;
	int	k;
	int	bool;
	char	c;
	char	*newstr;
	char	*new_variable;
}	t_var;

typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	char	**options;
	int		argc;
	int		exit_status;
	int		wpid;
	int		off;
	int		*pid;
	int		nbr_cmd;
	int		*pipefd;
	int		fd_infile;
	int		fd_outfile;
	int		i;
}	t_cmd;

typedef struct s_ms
{
	char	*line;
	char	*temp;
	char	**env;
	char	**split_pipe;
	char	**split_chevron_in;
	char	**split_chevron_out;
	int		*limit_mode;
	int		boolean_outfile;
	int		boolean_infile;
	int		code_erreur1;
	int		code_erreur;
	int		sig;
	int		here;
	int		filed;
	int		i_heredoc;
}t_ms;

typedef struct s_cmd_lst
{
	int				infile_mode;
	int				outfile_mode;
	int				*limit_mode;
	char			**infile_name;
	char			**outfile_name;
	char			**cmd_option;
	struct s_cmd_lst	*next;
}t_cmd_lst;

int			nb_cote(char *str);
int			check_space_chevron(char *str);
int			bool_cote(char *str, int i);
int			nb_chevron(char *str, char c);
int			valid_cote(char *str, int i, char c);
int			malloc_new_variable(char *variable, char *envstring, int *j);
int			her_doc_check(char *str);
int			check_fine_cote(char *line, char c, char cote);
int			check_cote(char *line, char c);
int			exist_chevron(char *str);
int			check_pipe(char *str);
int			malloc_clear_quote(char *str, int i);
int			limit_mode_malloc(char *str);
int			len_dbl_tab(char *str, char c);
int			len_file(char *str, int i, char c);
int			rights_check_util(char *str, int *i, t_ms **ms, char c);
char		*strspace_cpy(char *str, int i);
char		**parsing(char *one_cmd, t_ms **ms);
char		**split_incurve(char *str, char c);
char		*set_dollar(char *str, t_ms **ms);
char		**find_file(char *str, char c);
char		*find_variable(char *str, int i);
char		*comp_env(char *str, t_ms **ms, int i);
char    *replace_variable(char *str, char *envstring, char *variable);
char    *replace_variable2(char *str, char *variable);
char		*put_space(char *str, char c, int *i, char *str2);
char		**clean_str(char **double_tab);
char		*clear_quote(char *str);
char		*warning_error(char *str, int i, t_ms **ms);
char		*neww_variable(char *new_variable, char *variable, char *envstring);
void		lstadd_back(t_cmd_lst **lst, t_cmd_lst *new);
void		lstclear(t_cmd_lst **cmd_lst);
void		free_tab(char	**tab, int i);
void		rights_check(char *str, t_ms **ms, char c);
void		print_map(char **map);
void		read_prompt(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms);
void		right_check_heredoc(char *str, t_ms **ms);
t_cmd_lst	*lstnew(char **double_tab, t_ms *ms);
t_cmd_lst	*make_cmd_lst(t_ms *ms);
void		handler_sigint(int signal);

//Pipex
char		*find_good_path(char **envp, char *cmd, t_cmd *cmd1);
char		**tab_option(char *cmd);
char		**make_tab_path(char **envp, char *cmd, t_cmd *cmd1);
void		error_management(int code_error, t_cmd *cmd);
void		free_cmd(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst);
void		last_cmd(t_cmd *cmd, char **envp, char **argv, int argc);
void		free_cmd2(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst);
void		here_doc(int argc, char **argv, t_cmd *cmd);
void		close_all(t_cmd *cmd);
void		redir(int start, int end, t_cmd *cmd);
void		free_cmd1(t_cmd *cmd);
void		file_error(int code_error, t_cmd_lst *cmd_lst, int i);
void		close_fd(t_cmd *cmd);
void		init_tab(t_cmd *cmd);
void		find_path(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst);
void		clear_lst(t_cmd_lst **cmd_lst);
 void		child(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst, t_ms *ms);
int			first_space(char *cmd);
int			ft_strcmp_n(char *str1, char *str2);
int			last_letter(char *cmd);
int			where(char *cmd);
int			lstsize(t_cmd_lst *cmd_lst);
int			pipex(t_cmd_lst *cmd_lst, t_ms *ms);
int			valid_cotev2(char *str, int i, char c);
int			bool_cotev2(char *str, int i);
int			no_pipe(t_cmd_lst *cmd_lst, t_ms *ms);
int			for_open(t_cmd_lst *cmd_lst, t_cmd *cmd, t_ms *ms);
int			tab_len(char **tab);
int			parent(t_cmd *cmd);
int			open_infile(t_cmd *cmd ,t_cmd_lst *cmd_lst, t_ms *ms);
int			open_outfile(t_cmd *cmd, t_cmd_lst *cmd_lst);

//Builtin
int			check_cd(t_cmd_lst *cmd_lst);
int			check_echo(t_cmd_lst *cmd_lst);
int			check_pwd(t_cmd_lst *cmd_lst);
int			check_env(t_cmd_lst *cmd_lst, t_ms *ms);
int			check_unset(t_cmd_lst *cmd_lst);
int			check_builtin(t_cmd_lst *cmd_lst, t_ms *ms);
int			check_exit(t_cmd_lst *cmd_lst);
int			check_replace(char *str, t_ms *ms, int i);
void			exit_builtin_pipex(t_cmd_lst *cmd_lst, t_cmd *cmd, t_ms *ms);
void			exit_builtin_execex(t_cmd_lst *cmd_lst, t_cmd *cmd, t_ms *ms, int status);
char		**unset_builtin(t_cmd_lst *cmd_lst, t_ms *ms);
char		**create_env(char *str, t_ms *ms);
char		**replace_env(char *str, t_ms *ms);
void		echo_builtin(char **tab, int bool);
void		cd_builtin(char **tab, char **envp);
void		pwd_builtin(void);
void		only_last(t_cmd_lst *cmd_lst, t_ms *ms, t_cmd *cmd, int status);
void		export_builtin(t_cmd_lst *cmd_lst, t_ms *ms);
void		env_builtin(t_ms *ms);

#endif