# include <readline/readline.h> // rl
# include <readline/history.h> // rl histroy
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname
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

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(char *content)
{
	t_list	*new_element;

	if (!content)
		return (NULL);
	new_element = (t_list *)malloc(sizeof(t_list));
	if (!new_element)
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		(ft_lstlast(*lst))->next = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

t_list	*ft_lstmap(char **lst)
{
	t_list	*head;
	t_list	*new_list;
	t_list	**rtn;
	size_t	i;

	if (!lst)
		return (NULL);
	head = NULL;
	i = 0;
	while (lst[i])
	{
		new_list = ft_lstnew(lst[i]);
		if (!new_list)
		{
			ft_lstclear(&head);
			return (NULL);
		}
		ft_lstadd_back(&head, new_list);
		i++;
	}
	return (head);
}

int	my_echo(t_list *arglst)
{
	int	exit_value; // 本家コード見た感じ0以外は無さそう? 強いて言うならwriteが失敗した時くらい?
	int	display_return;

	display_return = 1;
	exit_value = 0;
	arglst = arglst->next; // 最初に入っているechoを飛ばす
	if (arglst == NULL) // listの最後がnull埋めされている前提
	{
		write(1, "\n", 1);
		return (exit_value);
	}
	if (strncmp(arglst->content, "-n", 3) == 0)
	{
		display_return = 0;
		arglst = arglst->next;
	}
	while (arglst)
	{
		printf("%s", arglst->content);
		if (arglst->next)
			putchar(' ');
		arglst = arglst->next;
	}
	if (display_return)
		putchar('\n');
	return (exit_value);
}

int	main(int argc, char **argv, char **envp) // 引数はexecveの第二引数が来るものとして考える
{
	t_list	*arglst;
	t_list	*tmp;
	int	exit_value;

	if (argc == 1 || strncmp("echo", argv[1], 5) != 0)
	{
		write(STDERR_FILENO, "Bad argument\n", 13);
		return (0);
	}
	arglst = ft_lstmap(&argv[1]); // 線形リストの作成, 実装ではarglstが最初から引数で受け取っているものとする

	/* list作成確認 */
	// tmp = arglst;
	// while (arglst)
	// {
	// 	printf("%s\n", arglst->content);
	// 	arglst = arglst->next;
	// }
	// ft_lstclear(&tmp); // leak対策

	exit_value = my_echo(arglst);
	free(arglst);
	return (exit_value);
}