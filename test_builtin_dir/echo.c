#include "test_builtin.h"

int	my_echo(char **split_ln)
{
	int	exit_value; // 本家コード見た感じ0以外は無さそう? 強いて言うならwriteが失敗した時くらい?
	int	display_return;
	size_t	i;

	display_return = 1;
	exit_value = 0;
	i = 0;
	if (split_ln[++i] == NULL) // listの最後がnull埋めされている前提
	{
		write(1, "\n", 1);
		return (exit_value);
	}
	if (strncmp(split_ln[i], "-n", 3) == 0)
	{
		display_return = 0;
		i++;
	}
	while (split_ln[i])
	{
		printf("%s", split_ln[i]);
		if (split_ln[i + 1])
			putchar(' ');
		i++;
	}
	if (display_return)
		putchar('\n');
	return (exit_value);
}
