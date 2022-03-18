#include "test_builtin.h"

int	my_pwd(void)
{
	char	*pwd_buf;

	pwd_buf = getcwd(NULL, 0);
	if (pwd_buf == NULL)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd_buf);
	free(pwd_buf);
	return (EXIT_SUCCESS);
}
