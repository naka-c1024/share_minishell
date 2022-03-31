# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahirose <kahirose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 16:01:59 by kahirose          #+#    #+#              #
#    Updated: 2022/04/01 01:15:43 by kahirose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	lexer_and_parser
CC		:=	gcc
RM		:= rm -f
#CFLAGS	:= -Wall -Werror -Wextra

SRCS	:=	lexer_and_parser.c \
			tokenize.c \
			tokens_count.c \
			make_ast.c \
			make_ast_utils.c \
			parser.c

OBJDIR	:=	./objs
OBJS	:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
INCDIR	:= -I../../includes
LIBFT_PATH	=	../../libft/
LIBFT	:=	../../libft/libft.a

$(NAME)	: $(OBJS)
	make bonus -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(INCDIR) $(OBJS) $(LIBFT) -o $(NAME)
# ar rc $(NAME) $(OBJS)

$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

all		: $(NAME)

clean	:
	if [ -e $(OBJDIR) ]; then \
		rm -rf $(OBJDIR);\
	fi
# make clean -C $(LIBFT_PATH)

fclean	: clean
	$(RM) $(NAME)
# make fclean -C $(LIBFT_PATH)

re		: fclean all

.PHONY	: all clean fclean re
