/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 09:19:19 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 12:51:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

typedef struct		s_libft
{
	void			*content;
	struct s_libft	*next;
}					t_libft;

char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_lstsize(t_libft *lst);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);
long long	ft_atoi_l(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
t_libft		*ft_lstlast(t_libft *lst);
t_libft		*ft_lstmap(t_libft *lst, void *(*f)(void *), void (*del)(void *));
t_libft		*ft_lstnew(void *content);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		ft_lstadd_back(t_libft **alst, t_libft *new);
void		ft_lstadd_front(t_libft **alst, t_libft *new);
void		ft_lstclear(t_libft **lst, void (*del)(void*));
void		ft_lstdelone(t_libft *lst, void (*del)(void*));
void		ft_lstiter(t_libft *lst, void (*f)(void *));
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

#endif
