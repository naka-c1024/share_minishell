#include "test_builtin.h"

static char	*get_home_value(t_envlist *envlist)
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

static int	set_oldpwd(char *oldpwd, t_envlist **envlist)
{
	t_envlist	*newlist;

	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		print_error("cd: malloc", NULL, errno);
		return (1);
	}
	remove_duplicate("OLDPWD", envlist); // 重複している環境変数をあらかじめ削除
	newlist->key = ft_strdup("OLDPWD");
	newlist->value = ft_strdup(oldpwd);
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	return (0);
}

static int	set_pwd(t_envlist **envlist)
{
	char		*pwd;
	t_envlist	*newlist;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		// print_error("cd: getcwd", NULL, errno);
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		print_error("cd: malloc", NULL, errno);
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

static int	set_cd_env(char *oldpwd, t_envlist **envlist)
{
	int	exit_status;

	exit_status = 0;
	if (oldpwd)
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

	oldpwd = getcwd(NULL, 0); // nullの場合も無視
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
		print_error("cd", split_ln[1], errno);
		write(1, "ok\n", 3); // debug
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	write(1, "ko\n", 3); // debug
	return (set_cd_env(oldpwd, envlist));
}
