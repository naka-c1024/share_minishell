#include <readline/readline.h>
#include <stdio.h>
# include <readline/history.h> // rl_clear_history, add_history
#include <stdbool.h>
#include <stdlib.h>
#include "../libft/libft.h"


int main(void)
{
	char	*line;
	char	*temp;
	char	*temp0;
	int		flag;

	flag = 0;
	temp0 = ft_strdup("");
	while (!flag)
	{
		temp = readline("heredoc2>");
		if (ft_strchr(temp, '"'))
		{
			flag = 1;
		}
		line = ft_strjoin(temp0, temp);
		free(temp0);
		free(temp);
		temp0 = line;
	}
	printf("\"");
	printf("%s\n", line);
	free(line);
	return (0);
}
