/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:34:57 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/06 20:41:53 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef executor_h
# define executor_h

# include "../../libft/libft.h"
# include "../../includes/minishell.h"

// extern int	g_exit_status;

# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <string.h> // strerror

# include <limits.h> // macro
# include <stdint.h> // macro(linux)
# include <stdbool.h> // bool
# include <errno.h> // errno

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define PIPEIN 0
# define PIPEOUT 1
# define NOFILE -2
# define FD_MAX 256
# define PATH_PREFIX 4

//builtin redirection
#define IN 1
#define HERE 2
#define OUT 3

#define PIPE 1
#define SINGLE_QUOTE 2
#define DOUBLE_QUOTE 3


//builtinコマンド識別
# define MY_EXIT 0
# define MY_ECHO 1
# define MY_CD 2
# define MY_PWD 3
# define MY_UNSET 4
# define MY_ENV 5
# define MY_EXPORT 6

// typedef struct s_info
// {
// 	char		**envp;
// 	t_envlist	*envlist;
// 	t_ms_ast	*ms_ast;
// 	int			**pipefd;
// 	pid_t		*pid;//何に使うの？
// 	int			process_cnt;
// }	t_info;

typedef struct s_file_info
{
	// char	*in_file;
	// char	*out_file;
	bool	in_file;
	bool	out_file;
	int		in_redirect;
	int		out_redirect;
	int		in_fd;
	int		out_fd;
	int		tmp_stdin;
	int		tmp_stdout;
}	t_file_info;

typedef	struct s_heredoc_info
{
	int		*here_doc_pipe;
	bool	is_here_doc;
	char	*buffer;//executor_main51ではmallocしてないためfreeするとまずいように見える
	char	*delimiter;
}	t_heredoc_info;

typedef struct s_process_info
{
	t_list			*cmd_list;//これはft_lstnewでmallocされていないためms_astをfreeするならこれはfreeすべきでない
	char			*cmd_full_path;
	char			**cmd;
	int				section;
	t_file_info		*file_info;//free
	bool			is_here_doc;
	t_heredoc_info	*hrdc_info;//free
}	t_process_info;

// envlist.c
void		free_list(t_envlist *list);
void		ms_lstadd_back(t_envlist **lst, t_envlist *element);
// t_envlist	*create_envlist(char **envp);

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
int	exe_no_builtin_cmd(char **str, t_envlist *envlist);

// only_one_cmd.c
int	only_one_cmd(char **dbl_arr, t_envlist **envlist);

//ipc_with_pipe
int		ipc_table(t_ms_ast *ms_ast, t_envlist *envlist, size_t process_cnt);
void	child_exe(t_info *info, t_process_info *p_info, t_ms_ast *ast_node);
char	**lst_to_arr(t_list *arglst);
void	convert_to_cmd_full_path(t_info *info, t_process_info *p_info);
void	redirection_seqence(t_ms_ast *ast_node, t_process_info *p_info, t_info *info);
void	dup2_func(t_info *info, t_process_info *p_info);
void	close_func(t_info *info, t_process_info *p_info);
void	heredoc_dup2(t_info *info, t_process_info *proc_info);
void	heredoc_close(t_info *info, t_process_info *proc_info);
ssize_t	pipex_putstr(char *s);
void	free_process_info(t_process_info **proc_info_addr);
t_list	*ms_lstnew(char *content);

//single_builtin
bool			only_builtin_assign_func \
	(char builtin_list[7][7], t_ms_ast *ms_ast, char *cmd_name, t_envlist **envlist);
t_process_info	*serch_redirection(t_ms_ast *ms_ast, bool *is_success);
void			dup_and_close(t_process_info *proc_info);
void			restore_redirection(t_process_info *proc_info);
void			free_twod_array(char **darray);

//single_builtin set_file
bool	sb_set_in_file(t_process_info *proc_info, char *file_name);
bool	sb_set_out_file(t_process_info *proc_info, char *file_name, int redirect_type);
void	sb_set_heredoc(t_ms_ast *ast_node, t_process_info *proc_info);
int		is_some_redirect(char *one_token);

#endif // exe_cmd_h
