#include "test_builtin.h"

void	numeric_argument_required(char *str)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("my_shell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}
