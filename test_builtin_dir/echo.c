#include "test_builtin.h"

int	safe_putstr_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = 0;
	if (len < INT_MAX)
	{
		if (write(fd, s, len) == -1)
		{
			print_error("echo: write", s, errno);
			return (1);
		}
	}
	else
		while (i < len)
		{
			if (write(fd, &s[i++], sizeof(char)) == -1)
			{
				print_error("echo: write", &s[i], errno);
				return (1);
			}
		}
	return (0);
}

int	my_echo(char **split_ln)
{
	int		display_return;
	size_t	i;

	display_return = 1;
	i = 0;
	if (split_ln[++i] == NULL) // listの最後がnull埋めされている前提
	{
		if (safe_putstr_fd("\n", STDOUT_FILENO))
			return (1);
		return (0);
	}
	if (ft_strncmp(split_ln[i], "-n", 3) == 0)
	{
		display_return = 0;
		i++;
	}
	while (split_ln[i])
	{
		if (safe_putstr_fd(split_ln[i], STDOUT_FILENO))
			return (1);
		if (split_ln[i + 1])
			if (safe_putstr_fd(" ", STDOUT_FILENO))
				return (1);
		i++;
	}
	if (display_return)
		if (safe_putstr_fd("\n", STDOUT_FILENO))
			return (1);
	return (0);
}
