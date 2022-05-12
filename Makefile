# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 20:31:40 by ynakashi          #+#    #+#              #
#    Updated: 2022/05/09 05:46:11 by kahirose         ###   ########.fr        #
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

VPATH	:=	srcs:srcs/expander:srcs/executor:srcs/utils:srcs/here_doc_input
SRCS	:=	main.c\
			here_doc_input.c\
			executor_main.c\
			expander_main.c

RL_PATH	:=/usr/local/opt/readline
RL_INCDIR	:=	-I$(RL_PATH)/include -I $(shell brew --prefix readline)/include
RL_ARC	:=	-L$(RL_PATH)/lib -L$(shell brew --prefix readline)/lib -lreadline -lhistory

INCDIR	:= -I./includes
OBJDIR	:=	./objs
OBJS := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT_PATH		=	./libft/
LIBFT_ARC		=	-Llibft -lft
LE_PA_PATH		=	./srcs/lexer_and_parser/
LE_PA_ARC		=	./srcs/lexer_and_parser/lexer_and_parser
HDI_PA_PATH		=	./srcs/here_doc_input/
HDI_PA_ARC		=	./srcs/here_doc_input/here_doc_input
SIGNAL_PATH		=	./srcs/signal/
SIGNAL_ARC		=	-L./srcs/signal -lsignal
EXE_CMD_PATH	=	./srcs/executor/
EXE_CMD_ARC		=	./srcs/executor/executor

$(NAME)	: $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(LE_PA_PATH)
	make -C $(HDI_PA_PATH)
	make -C $(SIGNAL_PATH)
	make -C $(EXE_CMD_PATH)
	$(CC) $(CFLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(HDI_PA_ARC) $(LE_PA_ARC) $(SIGNAL_ARC) $(EXE_CMD_ARC) -o $(NAME)

# suffix rule
$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

all		: $(NAME)

clean	:
	make clean -C $(LIBFT_PATH)
	make clean -C $(LE_PA_PATH)
	make clean -C $(HDI_PA_PATH)
	make clean -C $(SIGNAL_PATH)
	make clean -C $(EXE_CMD_PATH)
	if [ -e $(OBJDIR) ]; then \
		rm -rf $(OBJDIR);\
	fi

fclean	: clean
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(LE_PA_PATH)
	make fclean -C $(HDI_PA_PATH)
	make fclean -C $(SIGNAL_PATH)
	make fclean -C $(EXE_CMD_PATH)
	$(RM) $(NAME)

re		: fclean all

bonus	: $(NAME)

# ^Cなどを消す設定方法
rloff	:
	echo 'set echo-control-characters off' >> ~/.inputrc

nm		: fclean $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(LE_PA_PATH)
	make -C $(HDI_PA_PATH)
	make -C $(SIGNAL_PATH)
	make -C $(EXE_CMD_PATH)
	$(CC) $(CFLAGS) $(NO_BUILTIN_FLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(HDI_PA_ARC) $(LA_PA_ARC) $(SIGNAL_ARC) $(EXE_CMD_ARC) -o $(NAME)
	nm -u $(NAME)

debug	: fclean $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(LE_PA_PATH)
	make -C $(HDI_PA_PATH)
	make -C $(SIGNAL_PATH)
	make -C $(EXE_CMD_PATH)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(HDI_PA_ARC) $(LA_PA_ARC) $(SIGNAL_ARC) $(EXE_CMD_ARC) -o $(NAME)

leak	:
	leaks -quiet -atExit -- ./$(NAME)

.PHONY	: all clean fclean re bonus rloff nm debug leak
