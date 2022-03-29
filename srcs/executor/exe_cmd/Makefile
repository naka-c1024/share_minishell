# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 15:34:53 by ynakashi          #+#    #+#              #
#    Updated: 2022/03/29 15:53:37 by ynakashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	libexe_cmd.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

SRCS	=	cd.c\
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
			only_one_cmd.c

OBJDIR	:=	./objs
OBJS := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# suffix rule
$(OBJDIR)/%.o:	%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

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
