#include "lexer_and_parser.h"

static int	tl_len_count(char *line)
{
	int	tl_len;

	tl_len = 30;
	return (tl_len);
}

void	free_tokenize_info(t_tokenize_info **t_info)
{
	int	index;

	index = 0;
	if ((*t_info)->tokenized_line)
		while ((*t_info)->tokenized_line[index])
			free((*t_info)->tokenized_line[index++]);
	// free((*t_info)->line);//ここは後ほどmainと繋がってから
	free(*t_info);
	*t_info = NULL;
}

void	error_occuration_at_tokenize(t_tokenize_info **t_info, bool is_syntax)
{
	if (t_info)
		free_tokenize_info(t_info);
	if (is_syntax)
	{
		printf("syntax_error\n");
		exit(258);
	}
	printf("error\n");
	exit (1);
}

static bool	is_valid_pre_string(int line_index, char target)
{
	if (line_index == 0 || target == '|' || target == ' ' || \
		target == '"' || target == '\'' || target == '>' || target == '<')
			return (false);
	return (true);
}

static void	take_pre_string(t_tokenize_info *t_info)
{
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
	{
		t_info->tokenized_line[(*(t_info->tl_index))++] = \
			ft_substr(t_info->line, *(t_info->line_start_index), \
				*(t_info->line_index) - *(t_info->line_start_index));
		if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
			error_occuration_at_tokenize(&t_info, false);
	}
}

static void	take_last_string(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	t_info->tokenized_line[*(t_info->tl_index)] = NULL;
	last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '>' || last_token == '<')
		error_occuration_at_tokenize(&t_info, true);
	// free(line);//free_lexer_infoと同じくここも後ほど
	free(t_info);
}

static void	quote_separator(t_tokenize_info *t_info)
{
	char	target;

	target = t_info->line[*(t_info->line_index)];
	(*(t_info->line_index))++;
	while (t_info->line[*(t_info->line_index)] && \
			t_info->line[*(t_info->line_index)] != target)
		(*(t_info->line_index))++;
	if (t_info->line[*(t_info->line_index)] != target)
		error_occuration_at_tokenize(&t_info, true);
	(*(t_info->line_index))++;
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, *(t_info->line_start_index), \
			*(t_info->line_index) - *(t_info->line_start_index));
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_start_index) = *(t_info->line_index);
}

static void	pipe_separator(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	if (*(t_info->tl_index) == 0)
		error_occuration_at_tokenize(&t_info, true);
	last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '<')//リダイレクトでも'>'こっち向きは実行できるっぽい
		error_occuration_at_tokenize(&t_info, true);
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, (*(t_info->line_index))++, 1);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_start_index) = *(t_info->line_index);
}

static void	single_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
			error_occuration_at_tokenize(&t_info, true);
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, (*(t_info->line_index))++, 1);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_start_index) = *(t_info->line_index);
}

static	void	double_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
			error_occuration_at_tokenize(&t_info, true);
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, *(t_info->line_index), 2);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_index) += 2;
	*(t_info->line_start_index) = *(t_info->line_index);
}

static void	space_separator(t_tokenize_info *t_info)
{
	take_pre_string(t_info);
	while (t_info->line[*(t_info->line_index)] == ' ')
		(*(t_info->line_index))++;
	*(t_info->line_start_index) = *(t_info->line_index);
}

static	bool is_quote(t_tokenize_info *t_info)
{
	if (t_info->line[*(t_info->line_index)] == '\'' || \
		t_info->line[*(t_info->line_index)] == '"' )
			return (true);
	return (false);
}

static	bool is_single_redirect(t_tokenize_info *t_info)
{
	if (t_info->line[*(t_info->line_index)] == '>' || \
		t_info->line[*(t_info->line_index)] == '<')
				return (true);
	return (false);
}

static	bool is_double_redirect(t_tokenize_info *t_info)
{
	if (!ft_strncmp(&(t_info->line[*(t_info->line_index)]), ">>", 2) || \
		!ft_strncmp(&(t_info->line[*(t_info->line_index)]), "<<", 2))
			return (true);
	return (false);
}

static char **tokenize(t_tokenize_info *t_info)
{
	char	**tokenized_line;
	int		tl_len;

	tl_len = tl_len_count(t_info->line);
	tokenized_line = (char **)ft_calloc(sizeof(char *), tl_len);
	if (!tokenized_line)
		error_occuration_at_tokenize(&t_info, false);
	t_info->tokenized_line = tokenized_line;
	while (t_info->line[*(t_info->line_index)])
	{
		if (t_info->line[*(t_info->line_index)] == ' ')
			space_separator(t_info);
		else if (t_info->line[*(t_info->line_index)] == '|')
			pipe_separator(t_info);
		else if (is_quote(t_info))
				quote_separator(t_info);
		else if (is_double_redirect(t_info))
			double_redirect_separator(t_info);
		else if (is_single_redirect(t_info))
			single_redirect_separator(t_info);
		else
			(*(t_info->line_index))++;
	}
	take_last_string(t_info);
	return (t_info->tokenized_line);
}

char	**tokenize_main(char *line)
{
	t_tokenize_info	*t_info;
	int				line_index;
	int				line_start_index;
	char			**tokenized_line;
	int				tl_index;

	line_index = 0;
	line_start_index = 0;
	tl_index = 0;
	t_info = (t_tokenize_info *)malloc(sizeof(t_tokenize_info));
	if (!t_info)
		error_occuration_at_tokenize(NULL, false);
	t_info->line = line;
	t_info->line_index = &line_index;
	t_info->line_start_index = &line_start_index;
	t_info->tl_index = &tl_index;
	tokenized_line = tokenize(t_info);
	return (tokenized_line);
}

// int	main(void)
// {
// 	char 		*str = (char *)malloc(sizeof(char) * 100);
// 	str = "  cat file2|grep|'hel\"l\"o''aiueo'  | ||||\"wc -l    aal   |  |||";//スペースの後ろにセパレータが来るとまずい
// 	t_ms_ast	*ms_ast;
// 	char 		**tokenized_line;

// 	printf("%s\n", str);
// 	tokenized_line = tokenize_main(str);

// 	int i = 0;
// 	printf("exepected:[  cat file2|grep|'hel\"l\"o\'||||\"w'c -l    aal   |   |||]\n");
// 	printf("\n\nresult   :");
// 	while (tokenized_line[i])
// 	{
// 		if (!tokenized_line[i][0])
// 		{
// 			printf("\x1b[35m[null]\x1b[39m");
// 			i++;
// 		}
// 		else
// 			printf("[%s]", tokenized_line[i++]);
// 	}
// 	printf("\n");
// 	// ms_ast = lexer_and_parser(str);
// 	return(0);
// }
