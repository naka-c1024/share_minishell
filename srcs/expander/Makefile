# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 16:37:12 by ynakashi          #+#    #+#              #
#    Updated: 2022/06/18 08:25:50 by ynakashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	expander

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

SRCS	=	expander_main.c\
			expand_dollar.c\
			expand_quote.c

OBJDIR	=	./objs

OBJS	:=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

MSINCDIR	:= -I../../includes
HDIINCDIR	:= -I./

$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(MSINCDIR) $(HDIINCDIR) -c $< -o $@

$(NAME)	: $(OBJS)
	ar rc $(NAME) $(OBJS)

all		: $(NAME)

clean	:
	if [ -e $(OBJDIR) ]; then \
		rm -rf $(OBJDIR);\
	fi

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY: all clean fclean re
