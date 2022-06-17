# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 20:31:40 by ynakashi          #+#    #+#              #
#    Updated: 2022/06/17 17:10:51 by ynakashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell
CC		:=	gcc
RM		:=	rm -f
CFLAGS	:=	-Wall -Wextra -Werror

#DEBUG_FLAGS	:=	-g -fsanitize=address -fsanitize=undefined
DEBUG_FLAGS	:= -fsanitize=address -g3
# For M1MacBook, run the command below.
# export MallocNanoZone=0
# make debug
# unset MallocNanoZone
# env | grep Malloc
NO_BUILTIN_FLAGS	:=	-fno-builtin

VPATH	:=	srcs:srcs/expander:srcs/executor:srcs/utils:srcs/here_doc_input:srcs/signal
SRCS	:=	main.c\
			here_doc_input.c\
			executor_main.c\
			expander_main.c\
			xalloc1.c\
			xalloc2.c\
			free_array.c\
			safe_system_call.c\
			signal.c

RL_PATH	:=/usr/local/opt/readline
RL_INCDIR	:=	-I$(RL_PATH)/include -I $(shell brew --prefix readline)/include
RL_ARC	:=	 -L$(RL_PATH)/lib -L$(shell brew --prefix readline)/lib -lreadline -lhistory

INCDIR	:= -I./includes
OBJDIR	:=	./objs
OBJS := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT_PATH		=	./libft/
LIBFT_ARC		=	-Llibft -lft
LE_PA_PATH		=	./srcs/lexer_and_parser/
LE_PA_ARC		=	./srcs/lexer_and_parser/lexer_and_parser
HDI_PA_PATH		=	./srcs/here_doc_input/
HDI_PA_ARC		=	./srcs/here_doc_input/here_doc_input
EXE_CMD_PATH	=	./srcs/executor/
EXE_CMD_ARC		=	./srcs/executor/executor
EXPANDER_PATH	=	./srcs/expander/
EXPANDER_ARC	=	./srcs/expander/expander

$(NAME)	: $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(LE_PA_PATH)
	make -C $(HDI_PA_PATH)
	make -C $(EXE_CMD_PATH)
	make -C $(EXPANDER_PATH)
	$(CC) $(CFLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(HDI_PA_ARC) $(LE_PA_ARC) $(EXE_CMD_ARC) $(EXPANDER_ARC) -o $(NAME)

# suffix rule
$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

all		: $(NAME)

clean	:
	make clean -C $(LIBFT_PATH)
	make clean -C $(LE_PA_PATH)
	make clean -C $(HDI_PA_PATH)
	make clean -C $(EXE_CMD_PATH)
	make clean -C $(EXPANDER_PATH)
	if [ -e $(OBJDIR) ]; then \
		rm -rf $(OBJDIR);\
	fi

fclean	: clean
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(LE_PA_PATH)
	make fclean -C $(HDI_PA_PATH)
	make fclean -C $(EXE_CMD_PATH)
	make fclean -C $(EXPANDER_PATH)
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
	make -C $(EXE_CMD_PATH)
	make -C $(EXPANDER_PATH)
	$(CC) $(CFLAGS) $(NO_BUILTIN_FLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(HDI_PA_ARC) $(LE_PA_ARC) $(EXE_CMD_ARC) $(EXPANDER_ARC) -o $(NAME)
	nm -u $(NAME)

debug	: fclean $(OBJS)
	make bonus -C $(LIBFT_PATH)
	make -C $(LE_PA_PATH)
	make -C $(HDI_PA_PATH)
	make -C $(EXE_CMD_PATH)
	make -C $(EXPANDER_PATH)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCDIR) $(OBJS) $(RL_INCDIR) $(RL_ARC) $(LIBFT_ARC) $(HDI_PA_ARC) $(LE_PA_ARC) $(EXE_CMD_ARC) $(EXPANDER_ARC) -o $(NAME)

leak	:
	leaks -quiet -atExit -- ./$(NAME)

.PHONY	: all clean fclean re bonus rloff nm debug leak
