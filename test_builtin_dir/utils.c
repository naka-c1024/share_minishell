#include "test_builtin.h"

void	print_error(char *cmd, char *cmd_arg, int error_number)
{
	printf("my_shell: %s: %s: %s\n", cmd, cmd_arg, strerror(error_number));
}
