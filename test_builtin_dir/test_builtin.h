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

# define RL_MSG	"\033[33m""builtin test(lsも使える): ""\033[m"

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

// envlist.c
void		free_list(t_envlist *list);
t_envlist	*ms_lstlast(t_envlist *lst);
void		ms_lstadd_back(t_envlist **lst, t_envlist *new);
t_envlist	*create_envlist(char **envp);

// cd.c
char	*get_home_value(t_envlist *envlist);
int		set_oldpwd(char *oldpwd, t_envlist **envlist);
int		set_pwd(t_envlist **envlist);
int		set_cd_env(char *oldpwd, t_envlist **envlist);
int		my_cd(char **split_ln, t_envlist **envlist);

// echo.c
int		my_echo(char **split_ln);

// env.c
int		my_env(t_envlist *envlist);

// exit.c
long	my_atol(const char *str);
int		my_exit(char **split_ln);

// export.c
char	**list_to_array(t_envlist *envlist);
void	free_darray(char **darray);
int		my_strcmp(const char *s1, const char *s2);
char	**bubble_sort(char **darray);
void	print_export(t_envlist *envlist);
void	remove_duplicate(char *str, t_envlist **envlist);
int		set_new_node(char *str, t_envlist **envlist);
bool	can_export(char *str);
bool	is_equal(char *str);
bool	is_env_key(char *str, t_envlist *envlist);
int		no_equal(char *str, t_envlist **envlist);
void	not_a_valid_identifier(char *str);
int		set_env(char **split_ln, t_envlist **envlist);
int		my_export(char **split_ln, t_envlist **envlist);

// pwd.c
int		my_pwd(void);

// unset.c
int		my_unset(char **split_ln, t_envlist **envlist);

// utils.c
void	print_error(char *cmd, char *cmd_arg, int error_number);

#endif
