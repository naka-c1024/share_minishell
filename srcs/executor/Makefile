# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 15:34:53 by ynakashi          #+#    #+#              #
#    Updated: 2022/06/19 12:07:38 by kahirose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	executor

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

VPATH   :=  exe_cmd:ipc_with_pipe:single_builtin

IPCSRCS =	ipc_table.c\
			ipc_table_utils.c\
			ipc_executor.c\
			dup2_and_close.c\
			redirection_sequence.c\
			create_envlist.c\
			get_cmd_path.c

SBSRCS	=	single_builtin_executor.c\
			single_builtin_redirection.c\
			sb_serch_redirection.c\
			sb_set_file.c

EXESRCS	=	cd.c\
			echo.c\
			env.c\
			envlist.c\
			exit_utils.c\
			exit.c\
			export.c\
			export_lst_to_arr.c\
			export_print.c\
			export_set_env_utils.c\
			pwd.c\
			unset.c\
			utils.c\
			single_builtin_executor.c\
			executor_utils.c

SRCS	=	$(IPCSRCS) $(SBSRCS) $(EXESRCS)

OBJDIR	:=	./objs
OBJS := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

MSINCDIR	:= -I../../includes
EXINCDIR	:= -I./

# suffix rule
$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(MSINCDIR) $(EXINCDIR) -c $< -o $@

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
