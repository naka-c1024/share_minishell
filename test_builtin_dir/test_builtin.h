#ifndef TEST_BUILTIN_H
# define TEST_BUILTIN_H

# include "libft/libft.h"

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

# define RL_MSG	"\033[33m""cmd単体test: ""\033[m"

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

// envlist.c
void		free_list(t_envlist *list);
void		ms_lstadd_back(t_envlist **lst, t_envlist *new);
t_envlist	*create_envlist(char **envp);

// cd.c
int		my_cd(char **split_ln, t_envlist **envlist);

// echo.c
int		my_echo(char **split_ln);

// env.c
int		my_env(t_envlist *envlist);

// exit.c
int		my_exit(char **split_ln);

// exit_utils.c
void	numeric_argument_required(char *str);

// export.c
void	remove_duplicate(char *str, t_envlist **envlist);
int		my_export(char **split_ln, t_envlist **envlist);

// pwd.c
int		my_pwd(void);

// unset.c
int		my_unset(char **split_ln, t_envlist **envlist);

// no_builtin.c
int		cmd_exe(char **str, t_envlist *envlist);

// utils.c
void	safe_free(char **ptr);
void	free_split(char **ptr);
void	print_error(char *cmd, char *cmd_arg, int error_number);

// only_one_cmd.c
int	only_one_cmd(char **dbl_arr, t_envlist **envlist);

#endif
