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
// ここまではtestに必要な関数
/* -------------------------------------------- */
// ここからexport

void	print_export(t_envlist *envlist)
{
	t_envlist	*tmp;

	tmp = envlist;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "_", 2) == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	my_export(char **split_ln, t_envlist **envlist)
{
	if (split_ln[1] == NULL)
	{
		print_export(*envlist);
		return (0);
	}
	return (0);
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
		line = readline("\033[33m""export test(exit,unset,envも使える): ""\033[m"); // 入力受付
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			write(STDERR_FILENO, "exit\n", 5);
			safe_free(&line);
			free_list(envlist);
			return (EXIT_SUCCESS);
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
			return (EXIT_FAILURE);
		}
		if (ft_strncmp(split_ln[0], "unset", 6) == 0)
			exit_status = my_unset(split_ln, &envlist);
		else if (ft_strncmp(split_ln[0], "env", 4) == 0)
			exit_status = my_env(envlist);
		else if (ft_strncmp(split_ln[0], "export", 7) == 0)
		{
			exit_status = my_export(split_ln, &envlist); // ここを実装
		}
		else
			printf("Bad argument\n");
		add_history(line);
		safe_free(&line);
		split_free(split_ln);
	}
	return (exit_status);
}
