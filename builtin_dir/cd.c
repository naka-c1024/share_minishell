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

void	safe_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	split_free(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

void	free_list(t_envlist *list)
{
	t_envlist	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}
}

t_envlist	*ms_lstlast(t_envlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ms_lstadd_back(t_envlist **lst, t_envlist *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		(ms_lstlast(*lst))->next = new;
}

t_envlist	*create_envlist(char **envp)
{
	t_envlist	*head;
	t_envlist	*newlist;
	char	*str;

	head = NULL;
	while (*envp)
	{
		newlist = (t_envlist *)malloc(sizeof(t_envlist));
		if (!newlist)
		{
			perror("malloc");
			free_list(head);
			return (NULL);
		}
		str = *envp;
		while (*str && *str != '=')
			str++;
		*str = '\0';
		newlist->key = ft_strdup(*envp++);
		newlist->value = ft_strdup(++str);
		newlist->next = NULL;
		ms_lstadd_back(&head, newlist);
	}
	return (head);
}

int	my_env(t_envlist *envlist)
{
	while (envlist)
	{
		if (envlist->value == NULL)
		{
			envlist = envlist->next;
			continue ;
		}
		printf("%s=%s\n", envlist->key, envlist->value);
		envlist = envlist->next;
	}
	return (0);
}

int	my_unset(char **split_ln, t_envlist **envlist) // このenvlistを渡すと元の値も変わる
{
	size_t		i;
	t_envlist	*tmp;
	t_envlist	*eq_envptr;
	size_t		len;
	t_envlist	**cp_elist;

	i = 1;
	while (split_ln[i])
	{
		cp_elist = envlist;
		// cp_elistはenvlistの一番上のアドレスだけを複製しているから、
		// そこから辿るアクセスした配列は元のままなので、*cp_elistに代入すると値が書き変わってしまう
		while (*cp_elist)
		{
			len = ft_strlen(split_ln[i]);
			if (ft_strncmp(split_ln[i], (*cp_elist)->key, len + 1) == 0)
			{
				tmp = (*cp_elist)->next; // tmpは(*cp_elist使ってるから)元の値,envlistを書き換えたいからok
				free((*cp_elist)->key);
				free((*cp_elist)->value);
				free((*cp_elist));
				*cp_elist = tmp; // *cp_elistは元の値,envlistを書き換えたいからok
				break ;
			}
		// (*cp_elist) = (*cp_elist)->next; // これだと元の値を書き換えてしまうのでNG
			cp_elist = &(*cp_elist)->next;
		}
		i++;
	}
	return (0);
}

static size_t	list_cnt(t_envlist *envlist)
{
	size_t	i;

	i = 0;
	while (envlist)
	{
		envlist = envlist->next;
		i++;
	}
	return (i);
}

char	**list_to_array(t_envlist *envlist)
{
	char	**rtn;
	size_t	i;
	size_t	key_len;
	size_t	value_len;
	const size_t	else_len = 14; // null文字含めず(declare -x )+(=")+(")
	size_t	list_size;

	list_size = list_cnt(envlist);
	list_size -= 1; // -1してるのはアンダースコアがいらないから
	rtn = malloc(sizeof(char *) * (list_size) + 1);
	i = 0;
	while (envlist)
	{
		if (ft_strncmp(envlist->key, "_", 2) == 0)
		{
			envlist = envlist->next;
			continue ;
		}
		key_len = ft_strlen(envlist->key);
		if (envlist->value == NULL)
			value_len = 0;
		else
			value_len = ft_strlen(envlist->value);
		rtn[i] = (char *)malloc(key_len + value_len + else_len + 1);
		if (!rtn[i])
		{
			perror("malloc");
			return (NULL);
		}
		ft_strlcpy(rtn[i], "declare -x ", 11 + 1);
		ft_strlcat(rtn[i], envlist->key, 11 + key_len + 1);
		if (envlist->value == NULL)
		{
			envlist = envlist->next;
			i++;
			continue ;
		}
		ft_strlcat(rtn[i], "=\"", 11 + key_len + 2 + 1);
		ft_strlcat(rtn[i], envlist->value, 11 + key_len + 2 + value_len + 1);
		ft_strlcat(rtn[i], "\"", 11 + key_len + 2 + value_len + 1 + 1);
		envlist = envlist->next;
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

void	free_darray(char **darray)
{
	size_t	i;

	i = 0;
	while (darray[i])
	{
		free(darray[i]);
		i++;
	}
	free(darray);
}

char	**bubble_sort(char **darray)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	while (darray[i])
	{
		j = i + 1;
		while (darray[j])
		{
			if (strcmp(darray[i], darray[j]) > 0)
			{
				tmp = darray[i];
				darray[i] = darray[j];
				darray[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (darray);
}

void	print_export(t_envlist *envlist)
{
	char	**darray;
	size_t	i;

	darray = list_to_array(envlist);
	darray = bubble_sort(darray);
	i = 0;
	while (darray[i])
	{
		printf("%s\n", darray[i]);
		i++;
	}
	free_darray(darray);
}

void	remove_duplicate(char *str, t_envlist **envlist)
{
	t_envlist	**cp_elist;
	t_envlist	*tmp;
	size_t		len;

	cp_elist = envlist;
	while (*cp_elist)
	{
		len = ft_strlen(str);
		if (ft_strncmp(str, (*cp_elist)->key, len + 1) == 0)
		{
			tmp = (*cp_elist)->next;
			free((*cp_elist)->key);
			free((*cp_elist)->value);
			free((*cp_elist));
			*cp_elist = tmp;
			break ;
		}
		cp_elist = &(*cp_elist)->next;
	}
}

int	set_new_node(char *str, t_envlist **envlist)
{
	t_envlist	*newlist;
	char		*eq_location;
	t_envlist	**cp_elist;
	t_envlist	*tmp;
	size_t		len;

	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		perror("malloc");
		return (1);
	}
	eq_location = str;
	while (eq_location && *eq_location != '=')
		eq_location++;
	*eq_location = '\0'; // '='を'\0'に変える
	remove_duplicate(str, envlist); // 重複している環境変数をあらかじめ削除
	newlist->key = ft_strdup(str);
	newlist->value = ft_strdup(++eq_location);
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	return (0);
}

bool	can_export(char *str)
{
	size_t	i;

	if (ft_isdigit(str[0]))
		return (false);
	i = 0;
	while (str[i] && str[i] != '=') // メタ文字は無視
	{
		if ('#' <= str[i] && str[i] <= '/')
			return (false);
		else if (str[i] == ':' || str[i] == '?' || str[i] == '@')
			return (false);
		else if ('[' <= str[i] && str[i] <= '^')
			return (false);
		i++;
	}
	return (true);
}

bool	is_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_env_key(char *str, t_envlist *envlist)
{
	size_t	len;

	len = ft_strlen(str);
	while (envlist)
	{
		if (ft_strncmp(str, envlist->key, len + 1) == 0) // +1するのはnull文字まで見るため
			return (true);
		envlist = envlist->next;
	}
	return (false);
}

int	no_equal(char *str, t_envlist **envlist)
{
	t_envlist	*newlist;
	t_envlist	**cp_elist;
	t_envlist	*tmp;
	size_t		len;

	if (is_env_key(str, *envlist) == true) // すでにkeyがある場合は何もしない
	{
		return (0);
	}
	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		perror("malloc");
		return (1);
	}
	newlist->key = ft_strdup(str);
	newlist->value = NULL; // valueをnullにしている,envもexport単体もvalueがnullかどうかで出力をコントロールする
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	return (0);
}

int	set_env(char **split_ln, t_envlist **envlist)
{
	size_t	i;
	int		exit_status;

	exit_status = 0;
	i = 1;
	while (split_ln[i])
	{
		if (can_export(split_ln[i]) == false)
		{
			printf("bash: export: `%s': not a valid identifier\n", split_ln[i]);
			exit_status = 1;
		}
		else if (is_equal(split_ln[i]) == false)
		{
			if (exit_status == 1)
				no_equal(split_ln[i], envlist); // valueがないパターンの関数
			else if (exit_status == 0)
				exit_status = no_equal(split_ln[i], envlist); // valueがないパターンの関数
		}
		else if (exit_status == 1)
			set_new_node(split_ln[i], envlist);
		else if (exit_status == 0)
			exit_status = set_new_node(split_ln[i], envlist);
		i++; // norm対応でここを消す
	}
	return (exit_status);
}

int	my_export(char **split_ln, t_envlist **envlist)
{
	int	exit_status;

	exit_status = 0;
	if (split_ln[1] == NULL)
	{
		print_export(*envlist);
		return (exit_status);
	}
	else
	{
		exit_status = set_env(split_ln,envlist);
	}
	return (exit_status);
}
// ここまではtestに必要な関数
/* -------------------------------------------- */
// ここからcd
char	*get_home_value(t_envlist *envlist)
{
	size_t	len;

	len = ft_strlen("HOME");
	while (envlist)
	{
		if (ft_strncmp("HOME", envlist->key, len + 1) == 0) // +1するのはnull文字まで見るため
			return (envlist->value);
		envlist = envlist->next;
	}
	return (NULL);
}

int	set_oldpwd(char *oldpwd, t_envlist **envlist)
{
	t_envlist	*newlist;

	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		perror("malloc");
		return (1);
	}
	remove_duplicate("OLDPWD", envlist); // 重複している環境変数をあらかじめ削除
	newlist->key = ft_strdup("OLDPWD");
	newlist->value = ft_strdup(oldpwd);
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	return (0);
}

int	set_pwd(t_envlist **envlist)
{
	char	*pwd;
	t_envlist	*newlist;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		perror("malloc");
		free(pwd);
		return (1);
	}
	remove_duplicate("PWD", envlist); // 重複している環境変数をあらかじめ削除
	newlist->key = ft_strdup("PWD");
	newlist->value = ft_strdup(pwd);
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	free(pwd);
	return (0);
}

int	set_cd_env(char *oldpwd, t_envlist **envlist)
{
	int	exit_status;

	exit_status = set_oldpwd(oldpwd, envlist);
	if (exit_status == 1)
		set_pwd(envlist);
	else
		exit_status = set_pwd(envlist);
	free(oldpwd);
	return (exit_status);
}

int	my_cd(char **split_ln, t_envlist **envlist)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (split_ln[1] == NULL)
	{
		if (chdir(get_home_value(*envlist)) == -1)
		{
			ft_putstr_fd("my_shell: cd: HOME not set\n", STDERR_FILENO);
			free(oldpwd);
			return (1);
		}
		return (set_cd_env(oldpwd, envlist));
	}
	if (chdir(split_ln[1]) == -1)
	{
		perror("cd"); // ここのerror文をbashに合わせる
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	return (set_cd_env(oldpwd, envlist));
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split_ln;
	int		exit_status;
	pid_t	pid;
	int		status;

	t_envlist	*envlist;
	exit_status = EXIT_SUCCESS;

	envlist = create_envlist(envp); // freeするときはfree_list(envlist)する

	while (1)
	{
		line = readline("\033[33m""cd test(exit,pwd,ls,export,unset,envも使える): ""\033[m"); // 入力受付
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			write(STDERR_FILENO, "exit\n", 5);
			safe_free(&line);
			free_list(envlist);
			return (exit_status);
		}
		if (ft_strlen(line) == 0) // 改行だけの場合,空文字列がくる
		{
			safe_free(&line);
			continue ;
		}
		split_ln = ft_split(line, ' ');
		if (!split_ln)
		{
			safe_free(&line);
			free_list(envlist);
			return (EXIT_FAILURE);
		}
		if (ft_strncmp(split_ln[0], "cd", 3) == 0)
		{
			exit_status = my_cd(split_ln, &envlist);
		}
		else if (ft_strncmp(split_ln[0], "pwd", 4) == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				safe_free(&line);
				free_list(envlist);
				return (EXIT_FAILURE);
			}
			else if (pid == 0) // 子プロセスは親プロセスのデータをコピーしただけで書き換えることはできない
			{
				if (execve("/bin/pwd", split_ln, envp) == -1)
				{
					perror("execve");
					return (EXIT_FAILURE);
				}
			}
			else
			{
				if (wait(&status) < 0)
				{
					write(STDERR_FILENO, "\n", 1);
					split_free(split_ln);
					safe_free(&line);
					free_list(envlist);
					return (EXIT_FAILURE);
				}
			}
		}
		else if (ft_strncmp(split_ln[0], "ls", 3) == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				safe_free(&line);
				return (EXIT_FAILURE);
			}
			else if (pid == 0) // 子プロセスは親プロセスのデータをコピーしただけで書き換えることはできない
			{
				if (execve("/bin/ls", split_ln, envp) == -1)
				{
					perror("execve");
					return (EXIT_FAILURE);
				}
			}
			else
			{
				if (wait(&status) < 0)
				{
					write(STDERR_FILENO, "\n", 1);
					split_free(split_ln);
					safe_free(&line);
					free_list(envlist);
					return (EXIT_FAILURE);
				}
			}
		}
		else if (ft_strncmp(split_ln[0], "unset", 6) == 0)
			exit_status = my_unset(split_ln, &envlist);
		else if (ft_strncmp(split_ln[0], "env", 4) == 0)
			exit_status = my_env(envlist);
		else if (ft_strncmp(split_ln[0], "export", 7) == 0)
			exit_status = my_export(split_ln, &envlist);
		else
			printf("Bad argument\n");
		add_history(line); // 履歴の付け足し
		safe_free(&line);
		split_free(split_ln);
	}
	return (exit_status);
}
