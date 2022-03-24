#include "test_builtin.h"

int	my_unset(char **split_ln, t_envlist **envlist) // このenvlistを渡すと元の値も変わる
{
	size_t		i;
	t_envlist	*tmp;
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
