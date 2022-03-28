# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 14:21:38 by ynakashi          #+#    #+#              #
#    Updated: 2022/03/28 14:50:21 by ynakashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libsignal.a

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

SRCS	= signal.c

OBJS	= $(SRCS:.c=.o)

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	ar rc $(NAME) $(OBJS)

all		: $(NAME)

clean	:
	$(RM) $(OBJS) $(OBJS_B)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY: all clean fclean re
