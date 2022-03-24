/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:30:19 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/24 16:35:32 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

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

// rl_clear_history, rl_replace_line が見つからない
// ↑discordで検索, rl_clear_historyは使わないがrl_replace_line関数はsignalで^Cの時に使うから注意

# define RL_MSG	"\033[33m""my_shell ""\033[m"

//以下の数値をshell_astのtypeに入れノードの実態を判断
# define COMMAND 0
# define PIPE 1
# define LEFT 0
# define RIGHT 1

typedef	struct s_cmd_info
{
	// execve(info->cmd_full_path[cmd_index], info->cmd[cmd_index], info->envp);
	//上のexecveの引数用に以下のデータ構造を取る
	char	*cmd_full_path; // ex) "/bin/cat" 要らなそう
	char	**cmd_line; //  ex) "cat -e" ここをリストにする
	int		redirect; // redirect_listにしても良さそう（sudoさんの参考に)
}	t_cmd_info;

typedef	struct s_ms_ast
{
	int				type;
	t_list		*cmd_info_list;
	struct s_ms_ast		*left_node;
	struct s_ms_ast		*right_node;
}	t_ms_ast;

//以下の数値をcmd_infoのredirect変数に入れディスクリプタを管理
# define STDIN 0
# define STDOUT 1
# define STDERR 2

// signal
void	sigint_before_rl(int not_use);
void	sigint_after_rl(int not_use);
void	sigquit_after_rl(int not_use);
void	init_signal(int sig_num, void (*func)(int not_use));

//lexer_and_parser
char		***dp_to_tp(char **cmd_line);
t_ms_ast	*pipe_branch(char ***all_cmd_line);
t_ms_ast	*cmd_branch(char ****all_cmd_line_addr);
t_ms_ast	*new_cmd_node(char ****all_cmd_line_addr);
t_ms_ast	*new_pipe_node(t_ms_ast *left, t_ms_ast *right);

#endif
