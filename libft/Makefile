# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llai <llai@student.42london.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 09:38:33 by llai              #+#    #+#              #
#    Updated: 2024/03/26 18:03:02 by llai             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs
SRC = ft_isalpha.c \
      ft_isdigit.c \
      ft_isalnum.c \
      ft_isascii.c \
      ft_isprint.c \
      ft_strlen.c \
      ft_memset.c \
      ft_bzero.c \
      ft_memmove.c \
      ft_memcpy.c \
      ft_strlcpy.c \
      ft_strlcat.c \
      ft_toupper.c \
      ft_tolower.c \
      ft_strchr.c \
      ft_strrchr.c \
      ft_strncmp.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_strnstr.c \
      ft_atoi.c \
      ft_calloc.c \
      ft_strdup.c \
      ft_substr.c \
      ft_strjoin.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
	  ft_printf.c \
	  ft_print_char.c \
	  ft_flags_utils.c \
	  ft_print_str.c \
	  ft_print_digit.c \
	  ft_print_hex.c \
	  ft_print_unsigned_dec.c \
	  ft_print_ptr.c \
	  ft_atol.c \
	  ft_atoll.c \
	  get_next_line.c \
	  ft_lstnew.c \
	  ft_lstadd_front.c \
	  ft_lstsize.c \
	  ft_lstlast.c \
	  ft_lstadd_back.c \
	  ft_lstdelone.c \
	  ft_lstclear.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_lstget.c \
	  ft_lstiter_param.c \
	  ft_free.c
OBJS = $(SRC:.c=.o)

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(BONUS_OBJS)
	$(AR) $@ $^

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re bonus
