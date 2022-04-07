/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:30:19 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/06 17:41:51 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../srcs/signal/signal.h"
# include "../srcs/executor/exe_cmd/exe_cmd.h"

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

extern int	g_exit_status;

// typedef	struct s_cmd_info
// {
// 	// execve(info->cmd_full_path[cmd_index], info->cmd[cmd_index], info->envp);
// 	//上のexecveの引数用に以下のデータ構造を取る
// 	char	*cmd_full_path; // ex) "/bin/cat" 要らなそう
// 	char	**cmd_line; //  ex) "cat -e" ここをリストにする
// 	int		redirect; // redirect_listにしても良さそう（sudoさんの参考に)
// }	t_cmd_info;

typedef	struct s_ms_ast
{
	int				type;
	t_list		*cmd_info_list;
	struct s_ms_ast		*left_node;
	struct s_ms_ast		*right_node;
}	t_ms_ast;

// lexer_and_parser
t_ms_ast	*lexer_and_parser(char *line);

// expnader
void	expander(t_ms_ast **ms_ast, t_envlist *envlist);

// executor
void	executor(t_ms_ast *ms_ast, t_envlist **envlist);

#endif
