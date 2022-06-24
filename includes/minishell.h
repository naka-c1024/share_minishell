/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:30:19 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/19 22:56:43 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>

# define RL_MSG	"\033[33mmy_shell: \033[m"
# define COMMAND 0
# define PIPE 1
# define LEFT 0
# define RIGHT 1

extern int	g_exit_status;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_ms_ast
{
	int				type;
	t_list			*cmd_info_list;
	bool			is_here_doc;
	char			*buffer;
	char			*delimiter;
	struct s_ms_ast	*left_node;
	struct s_ms_ast	*right_node;
}	t_ms_ast;

typedef struct s_info
{
	char		**envp;
	t_envlist	*envlist;
	t_ms_ast	*ms_ast;
	int			**pipefd;
	pid_t		*pid;
	int			process_cnt;

}	t_info;

void		sigint_before_rl(int not_use);
void		sigint_after_rl(int not_use);
void		sigquit_after_rl(int not_use);
void		init_signal(int sig_num, void (*func)(int not_use));
void		sigint_after_rl_in_heredoc(int not_use);
void		sigint_after_rl_in_command_read(int not_use);
t_ms_ast	*lexer_and_parser(char **line, size_t *process_cnt);
bool		here_doc_init(t_ms_ast *ms_ast);
bool		expander(t_ms_ast **ms_ast, t_envlist *envlist);
void		executor(t_ms_ast *ms_ast, t_envlist **envlist, size_t process_cnt);
t_envlist	*create_envlist(char **envp);
void		safe_free(char **ptr);
void		free_split(char **ptr);
void		print_error(char *cmd, char *cmd_arg, int error_number);
void		free_three_d_arr(char ***three_d_line);
void		free_two_d_arr(char **two_d_line);
void		free_ast(t_ms_ast *ms_ast);
void		free_node(t_ms_ast *ms_ast);
void		list_clear(t_list *list);
int			safe_func(int result_status);
int			safe_func_with_file(int result_status, char *file_name);
void		*x_malloc(size_t size);
char		**ft_x_split(const char *s, char c);
char		*ft_x_strjoin(const char *s1, const char *s2);
void		*ft_x_calloc(size_t count, size_t size);
void		*ft_x_strdup(const char *s1);
char		*ft_x_substr(const char *s, unsigned int start, size_t len);
t_list		*ft_x_lstnew(void *content);
char		*ft_x_itoa(int n);
int			my_strcmp(const char *s1, const char *s2);

#endif
