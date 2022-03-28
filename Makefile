# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 20:31:40 by ynakashi          #+#    #+#              #
#    Updated: 2022/03/28 14:49:51 by ynakashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell
CC		:=	gcc
RM		:=	rm -f
# CFLAGS	:=	-Wall -Wextra -Werror

DEBUG_FLAGS	:=	-g -fsanitize=address -fsanitize=undefined
# For M1MacBook, run the command below.
# export MallocNanoZone=0
# make debug
# unset MallocNanoZone
# env | grep Malloc
NO_BUILTIN_FLAGS	:=	-fno-builtin

VPATH	:=	srcs:srcs/expander:srcs/executor:srcs/lexer_and_parser # これでSRCSに<./srcs/>を書かなくて済む
SRCS	:=	main.c\
			cd.c\
			no_builtin.c\
			echo.c\
			env.c\
			envlist.c\
			exit_utils.c\
			exit.c\
			export.c\
			pwd.c\
			unset.c\
			utils.c\
			only_one_cmd.c\
			tokenize.c\
			parser.c\
			make_ast.c\
			make_ast_utils.c\
			executor_main.c

RL_PATH	:=/usr/local/opt/readline
RL_INCDIR	:=	-I$(RL_PATH)/include -I $(shell brew --prefix readline)/include
RL_ARC	:=	-L$(RL_PATH)/lib -L$(shell brew --prefix readline)/lib -lreadline -lhistory

INCDIR	:= -I./includes
OBJDIR	:=	./objs
OBJS := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT_PATH	=	./libft/
LIBFT_ARC	=	-Llibft -lft

SIGNAL_PATH	=	./srcs/signal/
SIGNAL_ARC	=	-L./srcs/signal -lsignal

$(NAME)	: $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(SIGNAL_PATH)
	$(CC) $(CFLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(SIGNAL_ARC) -o $(NAME)

# suffix rule
$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

all		: $(NAME)

clean	:
	make clean -C $(LIBFT_PATH)
	make clean -C $(SIGNAL_PATH)
	if [ -e $(OBJDIR) ]; then \
		rm -rf $(OBJDIR);\
	fi

fclean	: clean
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(SIGNAL_PATH)
	$(RM) $(NAME)

re		: fclean all

bonus	: $(NAME)

# ^Cなどを消す設定方法
rloff	:
	echo 'set echo-control-characters off' >> ~/.inputrc

nm		: fclean $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(SIGNAL_PATH)
	$(CC) $(CFLAGS) $(NO_BUILTIN_FLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(SIGNAL_ARC) -o $(NAME)
	nm -u $(NAME)

debug	: fclean $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(SIGNAL_PATH)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(SIGNAL_ARC) -o $(NAME)

leak	:
	leaks -quiet -atExit -- ./$(NAME)

.PHONY	: all clean fclean re bonus rloff nm debug leak
