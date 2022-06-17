# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
    char *line;

    while (1)
    {
        line = readline("minishell ");
        if (strcmp(line, "exit") == 0)
        {
            write(STDERR_FILENO, "exit\n", 5);
            break ;
        }
        if (strcmp(line, "replace") == 0)
        {
            write(STDOUT_FILENO, "\n", 1);
            rl_replace_line("", 0); // 入力されたものをclear, m1macだとコンパイルできないためコメントアウトしている
            rl_on_new_line(); // 次の行に移動
            rl_redisplay(); // -再表示して以上の操作を画面上に反映
        }
        if (line && strlen(line) > 0)
        {
            printf("%s\n", line);
            add_history(line);
        }
        free(line);
    }
    return 0;
}
