# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 15:34:53 by ynakashi          #+#    #+#              #
#    Updated: 2022/05/09 05:23:37 by kahirose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	executor

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

VPATH   :=  exe_cmd:ipc_with_pipe

IPCSRCS =	ipc_table.c\
			ipc_executor.c\
			ipc_executor2.c\
			get_cmd_path.c

EXESRCS	=	cd.c\
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
			executor_utils.c

SRCS	=	$(IPCSRCS) $(EXESRCS)

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
