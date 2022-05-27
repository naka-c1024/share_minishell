# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 05:21:11 by kahirose          #+#    #+#              #
#    Updated: 2022/05/09 05:27:41 by kahirose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	here_doc_input

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

VPATH	=	get_next_line

HDISRCS	=	here_doc_input.c

GNLSRCS =	get_next_line.c\
			get_next_line_utils.c

SRCS	=	$(HDISRCS) $(GNLSRCS)

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
