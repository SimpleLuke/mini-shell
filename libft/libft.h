/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:15:44 by llai              #+#    #+#             */
/*   Updated: 2024/04/09 11:31:43 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

# if __linux__
#  define PTRNULL "(nil)"
# elif __APPLE__
#  define PTRNULL "0x0"
# endif

# define ISLOWER 0
# define ISUPPER 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* ----- Char ----- */
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

/* ----- String ----- */
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
long long	ft_atoll(const char *nptr);

/* ----- Memory ----- */
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);

/* ----- Additional ----- */
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

/* ----- File Descriptor ----- */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* ----- Bonus Linked List  ----- */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstget(t_list *lst, int index);
void		ft_lstiter_param(t_list *lst, void (*f)(void *, void *), void *ptr);

/* ************************************************************************** */
/*  ft_printf: Takes a string of format and arguments,                        */
/*             output a formatted string on stdout.                           */
/*             Returns the number of output characters.                       */
/* ************************************************************************** */
int			ft_printf(const char *format, ...);

/* ************************************************************************** */
/*  ft_istype: Takes an integer character,                                    */
/*             Returns 1 if it is one of the flags.                           */
/*             Returns 0 if it is not one of the flags.                       */
/* ************************************************************************** */
int			ft_istype(int c);

/* ************************************************************************** */
/*  ft_print_c: Takes a character and output on stdout.                       */
/*              Returns a count of 1.                                         */
/* ************************************************************************** */
int			ft_print_c(char c);

/* ************************************************************************** */
/*  ft_print_str: Takes a string (a pointer to a constant char).              */
/*                Output (null) if there is no string,                        */
/*                Otherwise, output the string.                               */
/*                Returns the count of the string.                            */
/* ************************************************************************** */
int			ft_print_str(const char *str);

/* ************************************************************************** */
/*  ft_print_digit: Takes an integer and convert it to a string.              */
/*                  Output the string on stdout.                              */
/*                  Returns the count of the string.                          */
/* ************************************************************************** */
int			ft_print_digit(int n);

/* ************************************************************************** */
/*  ft_print_hex: Takes an unsigned integer and depends if it is upper case,  */
/*                convert the integer to hexadecimal.                         */
/*                Output hexadecimal string on stdout.                        */
/*                Returns the count of the string.                            */
/* ************************************************************************** */
int			ft_print_hex(unsigned int n, int isupper);

/* ************************************************************************** */
/*  ft_print_unsigned_dec: Takes an unsigned integer,                         */
/*                         converts it to a string and output on stdout.      */
/*                         Returns the count of the string.                   */
/* ************************************************************************** */
int			ft_print_unsigned_dec(unsigned int n);

/* ************************************************************************** */
/*  ft_print_ptr: Takes an unsigned long integer,                             */
/*                output null pointer if it is zero.                          */
/*                Otherwise, it outputs hexadecimal format.                   */
/*                Returns the count of the output string.                     */
/* ************************************************************************** */
int			ft_print_ptr(unsigned long int n);

char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *s1, const char *s2, size_t len);
void		ft_free(void **ptr);
void		ft_lstdelone1(t_list *lst, void (*del)(void **));
void		ft_lstclear2(t_list **lst, void (*del)(void **));
void		ft_free_strarr(char ***arr);

#endif
