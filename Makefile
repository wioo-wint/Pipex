# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 12:54:11 by wintoo            #+#    #+#              #
#    Updated: 2025/10/17 20:21:55 by wintoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CC 		= cc
CCFlags = -Wall -Wextra -Werror -g3

SRCS	= src/main.c src/pipex.c src/let_it_free.c src/error.c src/find_and_exe.c \
		libft/ft_split.c libft/ft_strncmp.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strchr.c \
		bonus/get_next_line.c bonus/pipex_bonus.c

OBJS	= $(SRCS:.c=.o)

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CCFlags) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CCFlags) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re