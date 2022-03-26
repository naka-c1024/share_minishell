#include "test_builtin.h"

int	only_one_cmd(char **dbl_arr, t_envlist **envlist)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ft_strncmp(dbl_arr[0], "exit", 5) == 0)
	{
		exit_status = my_exit(dbl_arr);
		if (exit_status != 1) // これ大事, 1の時はexitしない、しかしexit 1や前のexit_statusが1の時はexitする, ここでmallocしてるもの全てfreeする
			exit(exit_status);
	}
	else if (ft_strncmp(dbl_arr[0], "echo", 5) == 0)
		exit_status = my_echo(dbl_arr);
	else if (ft_strncmp(dbl_arr[0], "cd", 3) == 0)
		exit_status = my_cd(dbl_arr, envlist);
	else if (ft_strncmp(dbl_arr[0], "pwd", 4) == 0)
		exit_status = my_pwd();
	else if (ft_strncmp(dbl_arr[0], "unset", 6) == 0)
		exit_status = my_unset(dbl_arr, envlist);
	else if (ft_strncmp(dbl_arr[0], "env", 4) == 0)
		exit_status = my_env(*envlist);
	else if (ft_strncmp(dbl_arr[0], "export", 7) == 0)
		exit_status = my_export(dbl_arr, envlist);
	else
		exit_status = cmd_exe(dbl_arr, *envlist);
	return (exit_status);
}
