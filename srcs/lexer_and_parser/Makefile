# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 16:01:59 by kahirose          #+#    #+#              #
#    Updated: 2022/03/29 11:55:09 by kahirose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	lexer_and_parser
CC		:=	gcc
RM		:= rm -f
#CFLAGS	:= -Wall -Werror -Wextra

SRCS	:=	tokenize.c make_ast.c make_ast_utils.c parser.c
OBJDIR	:=	./objs
OBJS	:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
INCDIR	:= -I../../includes
LIBFT_PATH	=	../../libft/
LIBFT	:=	../../libft/libft.a

$(NAME)	: $(OBJS)
	ar rc $(NAME) $(OBJS)
#make bonus -C $(LIBFT_PATH)
# $(CC) $(CFLAGS) $(INCDIR) $(OBJS) $(LIBFT) -o $(NAME)

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
