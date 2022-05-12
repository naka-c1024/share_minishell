# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 16:01:59 by kahirose          #+#    #+#              #
#    Updated: 2022/05/09 05:09:49 by kahirose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	lexer_and_parser
CC		:=	gcc #-fsanitize=address -g3
RM		:= rm -f
#CFLAGS	:= -Wall -Werror -Wextra

VPATH   :=  tokenize:split_by_pipe:make_ast:debug_utils:../utils
SRCS	:=	lexer_and_parser_main.c \
			tokenize.c \
			tokens_count.c \
			make_ast_main.c \
			make_ast_exe.c \
			make_ast_utils.c \
			error_tokenize.c \
			split_by_pipe.c \
			free_ast.c \
			print_data.c

OBJDIR	:=	./objs
OBJS	:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
MSINCDIR	:= -I../../includes
LPINCDIR	:= -I./
LIBFT_PATH	=	../../libft/
LIBFT	:=	../../libft/libft.a

$(NAME)	: $(OBJS)
	make bonus -C $(LIBFT_PATH)
	ar rc $(NAME) $(OBJS)
# $(CC) $(CFLAGS) $(MSINCDIR) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(MSINCDIR) $(LPINCDIR) -c $< -o $@

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
