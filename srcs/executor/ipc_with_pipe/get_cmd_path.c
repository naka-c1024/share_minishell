#include "executor.h"

char	**lst_to_arr(t_list *arglst)
{
	char	**rtn;
	size_t	i;
	t_list	*cp_arglst;
	size_t	list_cnt;
	size_t	content_len;

	cp_arglst = arglst;
	list_cnt = 0;
	while (cp_arglst)
	{
		list_cnt++;
		cp_arglst = cp_arglst->next;
	}
	rtn = (char **)malloc(sizeof(char *) * (list_cnt + 1));
	if (!rtn)
		return (NULL);
	i = 0;
	while (arglst)//何でdupを使ってないんだろう
	{
		content_len = ft_strlen(arglst->content);
		rtn[i] = (char *)malloc(sizeof(char) * content_len + 1);
		if (!rtn[i])
		{
			perror("malloc");
			// free_2darray(rtn);
			return (NULL);
		}
		ft_strlcpy(rtn[i], arglst->content, content_len + 1);
		arglst = arglst->next;
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

static bool	cmd_seaching(t_info *info, t_process_info *p_info, char **all_paths)
{
	int		path_index;
	char	*temp;

	path_index = 0;
	while (all_paths[path_index])
	{
		temp = ft_strjoin(all_paths[path_index], "/");
		p_info->cmd_full_path = ft_strjoin(temp, p_info->cmd[0]);
		free(temp);
		if (!p_info->cmd_full_path)
		{
			// free_2arr((void ***)&all_paths);
			// exit(free_all_info(info, true, 1));
			;
		}
		if (!access(p_info->cmd_full_path, X_OK))
		{
			// free_2arr((void ***)&all_paths);
			return (true);
		}
		free(p_info->cmd_full_path);
		p_info->cmd_full_path = NULL;
		path_index++;
	}
	return (false);
	info = NULL;//unused回避用
}

// static bool	is_full_path_case(t_processs_info *p_info)
// {
// 	if (!access(p_info->cmd[0], X_OK))
// 	{
// 		p_info->cmd_full_path = ft_strdup(p_info->cmd[0]);
// 		return (true);
// 	}
// 	return (false);
// }

static	char	**get_all_paths(t_info *info)
{
	char		**all_paths;
	t_envlist	*role_envlist;

	role_envlist = info->envlist;
	while (role_envlist)
	{
		if (!ft_strncmp(role_envlist->key, "PATH", PATH_PREFIX))
		{
			all_paths = ft_split(role_envlist->value, ':');
			if (!all_paths)
				return (NULL);
			return (all_paths);
		}
		role_envlist = role_envlist->next;
	}
	return (NULL);
}

void	convert_to_cmd_full_path(t_info *info, t_process_info *p_info)
{
	char	**all_paths;
	// int		path_index;

	// if (is_full_path_case(info))
	// 	return ;
	all_paths = get_all_paths(info);
	// if (!all_paths)
	// 	exit(free_all_info(info, true, 1));
	if (cmd_seaching(info, p_info, all_paths))
	{
		// printf("%s\n", p_info->cmd_full_path);
		return ;
	}
	return ;
	p_info->cmd_full_path = ft_strdup("");
	// free_2arr((void ***)&all_paths);
	write(STDERR_FILENO, "pipex: command not found: ", 26);
	ft_putendl_fd(p_info->cmd[0], STDERR_FILENO);
}
