/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:30:19 by ynakashi          #+#    #+#             */
/*   Updated: 2022/05/09 05:08:25 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../srcs/signal/signal.h"
// # include "../srcs/executor/executor.h"

extern int	g_exit_status;

# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h> // rl_clear_history, add_history
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <fcntl.h> // open
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h> // stat, lstat, fstat
# include <dirent.h> // opendir, readdir, closedir
# include <string.h> // strerror
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcsetattr, tcgetattr
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include <limits.h> // macro
# include <stdint.h> // macro(linux)
# include <stdbool.h> // bool
# include <errno.h> // errno

# define RL_MSG	"\033[33m""my_shell: ""\033[m"

//以下の数値をshell_astのtypeに入れノードの実態を判断
# define COMMAND 0
# define PIPE 1
// # define QUOTE 2
# define LEFT 0
# define RIGHT 1

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef	struct s_ms_ast
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
	char		**envp;//no
	t_envlist	*envlist;//malloc
	t_ms_ast	*ms_ast;//malloc
	int			**pipefd;//malloc
	pid_t		*pid;//malloc
	int			process_cnt;//no

}	t_info;

// typedef struct s_process_info
// {
// 	char	*cmd_full_path;//malloc
// 	char	**cmd;//malloc ms_astと別でさらにmallocしてる
// 	char	*file;//mallocする予定
// 	int		section;//no
// 	int		redirect;//mallocしない予定
// 	bool	is_here_doc;//no
// 	char	*total_document;//malloc
// 	char	*limiter;//mallocする予定
// }	t_process_info;

// lexer_and_parser
t_ms_ast	*lexer_and_parser(char *str, size_t *process_cnt);
void		here_doc_set(t_ms_ast *ms_ast);
void		free_ast(t_ms_ast *ms_ast);
void		free_node(t_ms_ast *ms_ast);

// expnader
void	expander(t_ms_ast **ms_ast, t_envlist *envlist);

// executor
t_envlist	*create_envlist(char **envp);
void		executor(t_ms_ast *ms_ast, t_envlist **envlist, char **envp, size_t process_cnt);

// exe_cmd/utils.c
void	safe_free(char **ptr);
void	free_split(char **ptr);
void	print_error(char *cmd, char *cmd_arg, int error_number);

//utils

#endif
