/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:59:05 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 15:58:01 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t size);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_lstsize(t_list *lst);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_count_struct(char *str);
int		ft_strlenn(const char *str);
int		free_line(char *line);
int		check_cara(char *str, char c, int boole);
int		no_new_line(char *buff, char **line, int fd, int *red);
int		init_read(char *buff, char **line, int *red, int fd);
int		ft_printf(int fd, const char *str, ...);
int		ft_strcmp(char *str1, char *str2);
int		ft_putnbr(int n, int *len, int fd);
int		ft_putchar_fd_printf(char c, int *len, int fd);
int		ft_putstr(char *str, int *len, int fd);
int		ft_putnbr_unsi(unsigned int n, int *len, int fd);
int		ft_putnb_base(unsigned int n, char *base, int *len, int fd);
int		ft_putvoid(void *ptr, int *len, int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strmalup(const char *str);
char	*get_next_line(int fd);
char	*join(char *s1, char *s2);
char	*substr(char *s, unsigned int start, size_t len);
void	init_str(char *buff, char c, int boole);
void	*ft_callocc(size_t elemCount, size_t elementSize);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *memoryBlock, int c, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *dest, int c, size_t size);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlen(const char *str);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif