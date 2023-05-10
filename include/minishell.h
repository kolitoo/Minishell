/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:51:32 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/10 16:24:26 by abourdon         ###   ########.fr       */
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
# include <signal.h>

typedef struct s_tab
{
	int	i;
	int	j;
	int	k;
}	t_tab;

typedef struct s_atoi
{
	int			i;
	int			sign;
	long long	nb;
	long long	old_nb;
}	t_atoi;

typedef struct s_var
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		bool;
	char	c;
	char	*newstr;
	char	*new_variable;
	char	*strfin;
	char	**tab;
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
	int		*tab_close_outfile;
	int		*tab_close_infile;
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
	int		j_heredoc;
	int		builtin_code;
	int		i_file;
}t_ms;

typedef struct s_cmd_lst
{
	int					infile_mode;
	int					outfile_mode;
	int					*limit_mode;
	char				**infile_name;
	char				**outfile_name;
	char				**cmd_option;
	struct s_cmd_lst	*next;
}t_cmd_lst;

int						nb_cote(char *str);
int						check_space_chevron(char *str, t_ms *ms,
							t_cmd_lst *cmd_lst);
int						bool_cote(char *str, int i);
int						nb_chevron(char *str, char c);
int						valid_cote(char *str, int i, char c);
int						malloc_new_variable(char *variable,
							char *envstring, int *j);
int						her_doc_check(char *str);
int						check_fine_cote(char *line, char c, char cote);
int						check_cote(char *line, char c);
int						exist_chevron(char *str);
int						check_pipe(char *str, int i);
int						limit_mode_malloc(char *str);
int						len_dbl_tab(char *str, char c);
int						len_file(char *str, int i, char c);
int						rights_check_util(char *str, int *i, t_ms **ms, char c);
char					*strspace_cpy(char *str, int i, t_ms **ms,
							t_cmd_lst *cmd_lst);
char					**parsing(char *one_cmd, t_ms **ms, t_cmd_lst *cmd_lst);
char					**split_incurve(char *str, char c, t_ms *ms,
							t_cmd_lst *cmd_lst);
char					**split_incurv3(char *str, char c, t_ms *ms,
							t_cmd_lst *cmd_lst);
char					**ft_split2(char const *s, char c);
char					*set_dollar(char *str, t_ms **ms, t_cmd_lst *cmd_lst);
char					**find_file(char *str, char c, t_ms *ms,
							t_cmd_lst *cmd_lst);
char					*find_variable(char *str, int i);
char					*comp_env(char *str, t_ms **ms, int i,
							t_cmd_lst *cmd_lst);
char					*replace_variable(char *str, char *envstring,
							char *variable, int k);
char					*replace_variable2(char *str, char *variable, int k);
char					*put_space(char *str, char c, int *i, char *str2);
char					**clean_str(char **double_tab, t_ms *ms,
							t_cmd_lst *cmd_lst);
char					*clear_quote(char *str, t_ms *ms, t_cmd_lst *cmd_lst);
char					*join2(char *s1, char *s2);
char					*warning_error(char *str, int i, t_ms **ms,
							t_cmd_lst *cmd_lst);
char					**set_env(char	**envp);
char					*neww_variable(char *new_variable, char *variable,
							char *envstring);
void					sig_for_child(void);
void					lstadd_back(t_cmd_lst **lst, t_cmd_lst *new);
void					lstclear(t_cmd_lst **cmd_lst);
void					free_tab(char	**tab, int i);
void					free_cd(char *s1, char *s2);
void					rights_check(char *str, t_ms **ms, char c);
void					read_prompt(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms);
void					read_prompt_condition(t_cmd *cmd, t_cmd_lst *cmd_lst,
							t_ms *ms);
void					right_check_heredoc(char *str, t_ms **ms,
							t_cmd_lst *cmd_lst);
void					handler_sigint(int signal);
void					free_builtin_export(t_ms *ms, t_cmd_lst *cmd_lst,
							char **new_envp);
void					free_builtin(t_ms *ms, t_cmd_lst *cmd_lst);
void					free_parsing(t_ms *ms, t_cmd_lst *cmd_lst, char *str);
void					free_make_cmd_lst(t_ms *ms, t_cmd_lst *cmd_lst,
							char **double_tab);
void					free_env_utils(char *new_variable, char *variable,
							char *str, int bool);
void					set_dollar3(char *str, int *i);
void					free_env_utils2(char *variable, char *str);
void					variable_util(t_var *var, char *str);
void					free_file(t_var *var, t_ms *ms, t_cmd_lst *cmd_lst);
void					launch_signal(void);
t_cmd_lst				*lstnew(char **double_tab, t_ms *ms);
t_cmd_lst				*make_cmd_lst(t_ms *ms);

//Pipex	
char					*find_good_path(char **envp, char *cmd, t_cmd *cmd1);
char					**tab_option(char *cmd);
char					**make_tab_path(char **envp, char *cmd, t_cmd *cmd1);
void					error_management(int code_error, t_cmd *cmd);
void					free_cmd(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst);
void					last_cmd(t_cmd *cmd, char **envp, char **argv,
							int argc);
void					free_cmd2(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst);
void					free_cmd4(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst);
void					here_doc(int argc, char **argv, t_cmd *cmd);
void					close_all(t_cmd *cmd);
void					free_cmd1(t_cmd *cmd);
void					file_error(int code_error, t_cmd_lst *cmd_lst,
							t_cmd cmd, t_ms *ms);
void					close_fd(t_cmd *cmd);
void					init_tab(t_cmd *cmd, t_cmd_lst *cmd_lst);
void					find_path(t_cmd *cmd, char **envp, t_cmd_lst *cmd_lst);
void					clear_lst(t_cmd_lst **cmd_lst);
void					child(t_cmd *cmd, char **envp,
							t_cmd_lst *cmd_lst, t_ms *ms);
void					init_tab_closefile(t_cmd *cmd,
							t_cmd_lst *cmd_lst, t_ms *ms);
void					close_fichier(t_cmd cmd, t_cmd_lst *cmd_lst,
							char **env);
int						redir(int start, int end, t_cmd *cmd);
int						ft_strcmp_n(char *str1, char *str2);
int						where(char *cmd);
int						lstsize(t_cmd_lst *cmd_lst);
int						pipex(t_cmd_lst *cmd_lst, t_ms *ms);
int						valid_cotev2(char *str, int i, char c);
int						bool_cotev2(char *str, int i);
int						no_pipe(t_cmd_lst *cmd_lst, t_ms *ms);
int						for_open(t_cmd_lst *cmd_lst, t_cmd *cmd, t_ms *ms);
int						tab_len(char **tab);
int						parent(t_cmd *cmd, t_ms *ms);
int						open_infile(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms);
int						open_outfile(t_cmd *cmd, t_cmd_lst *cmd_lst, t_ms *ms);

//Builtin	
int						check_cd(t_cmd_lst *cmd_lst);
int						check_echo(t_cmd_lst *cmd_lst, t_ms *ms,
							int i, t_cmd cmd);
int						check_pwd(t_cmd_lst *cmd_lst, t_ms *ms);
int						check_env(t_cmd_lst *cmd_lst, t_ms *ms);
int						check_unset(t_cmd_lst *cmd_lst);
int						check_builtin(t_cmd_lst *cmd_lst, t_ms *ms, t_cmd *cmd);
int						check_exit(t_cmd_lst *cmd_lst);
int						check_replace(char *str, t_ms *ms, int i, int bool);
int						check_egal(char *str);
int						check_if_unset(char *str, t_ms *ms);
int						pos_egal(char *str);
int						check_add(char *str, t_ms *ms);
int						check_backslashzero(t_var *var, char *str, t_ms *ms,
							t_cmd_lst *cmd_lst);
int						str_is_dig(char *str);
int						check_nbr(char *str);
int						pos_plus(char *str);
int						check_forbiden_cara(char *str);
char					**unset_builtin(t_cmd_lst *cmd_lst, t_ms *ms);
char					**create_env(char *str, t_ms *ms,
							t_cmd_lst *cmd_lst, int bool);
char					**replac_env(char *str, t_ms *ms,
							t_cmd_lst *cmd_lst, int bool);
char					**conca_env(char *str, t_ms *ms, t_cmd_lst *cmd_lst);
void					exit_builtin_execex(t_cmd_lst *cmd_lst, t_cmd *cmd,
							t_ms *ms, int status);
void					exit_builtin_pipex(t_cmd_lst *cmd_lst, t_ms *ms);
void					exit_builtin_free(t_cmd_lst *cmd_lst, t_ms *ms,
							long long arg_exit, t_cmd cmd);
void					echo_builtin(int bool, t_cmd_lst *cmd_lst,
							t_ms *ms, t_cmd cmd);
char					*dollar_last_check(char *str, t_ms **ms,
							t_cmd_lst *cmd_lst);
void					cd_builtin(char **tab, t_ms *ms,
							t_cmd_lst *cmd_lst);
void					cd_alone(char **envp, t_ms *ms,
							t_cmd_lst *cmd_lst);
void					pwd_builtin(t_ms *ms, t_cmd_lst *cmd_lst);
void					only_last(t_cmd_lst *cmd_lst, t_ms *ms, t_cmd *cmd,
							int status);
void					export_builtin(t_cmd_lst *cmd_lst, t_ms *ms);
void					env_builtin(t_ms *ms, t_cmd_lst *cmd_lst);
void					solo_export(t_ms *ms, t_cmd_lst *cmd_lst, int i, int j);
void					ft_atoi2(t_atoi *var, t_ms *ms, const char *str);
void					cd_localise( t_ms *ms, t_cmd_lst *cmd_lst);
unsigned long long		ft_atoi(const char *str, t_ms *ms);

#endif	