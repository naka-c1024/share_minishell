#include "test_builtin.h"

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
	char			**rtn;
	size_t			i;
	size_t			key_len;
	size_t			value_len;
	const size_t	else_len = 14; // null文字含めず(declare -x )+(=")+("),normで消すかも
	size_t			list_size;

	list_size = list_cnt(envlist);
	list_size -= 1; // -1してるのはアンダースコアがいらないから
	rtn = malloc(sizeof(char *) * (list_size) + 1);
	if (!rtn)
	{
		print_error("export: malloc", NULL, errno);
		return (NULL);
	}
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
			print_error("export: malloc", NULL, errno);
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

int	my_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	**bubble_sort(char **darray)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (darray[i])
	{
		j = i + 1;
		while (darray[j])
		{
			if (my_strcmp(darray[i], darray[j]) > 0)
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
	if (!darray)
		return ;
	darray = bubble_sort(darray);
	i = 0;
	while (darray[i])
	{
		ft_putendl_fd(darray[i], STDOUT_FILENO);
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
		print_error("export: malloc", NULL, errno);
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
		print_error("export: malloc:", NULL, errno);
		return (1);
	}
	newlist->key = ft_strdup(str);
	newlist->value = NULL; // valueをnullにしている,envもexport単体もvalueがnullかどうかで出力をコントロールする
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	return (0);
}

void	not_a_valid_identifier(char *str)
{
	ft_putstr_fd("my_shell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
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
			not_a_valid_identifier(split_ln[i]);
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