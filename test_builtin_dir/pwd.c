#include "test_builtin.h"

int	my_pwd(void)
{
	char	*pwd_buf;

	pwd_buf = getcwd(NULL, 0);
	if (pwd_buf == NULL)
	{
		print_error("pwd", NULL, errno);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd_buf, STDOUT_FILENO);
	free(pwd_buf);
	return (EXIT_SUCCESS);
}
