#include "test_builtin.h"

void	print_error(char *cmd, char *cmd_arg, int error_number)
{
	// printf("my_shell: %s: %s: %s\n", cmd, cmd_arg, strerror(error_number));
	ft_putstr_fd("my_shell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd_arg)
	{
		ft_putstr_fd(cmd_arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(strerror(error_number), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
