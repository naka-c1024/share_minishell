#include "lexer_and_parser.h"

static int	tl_len_count(char *line)
{
	int	tl_len;

	tl_len = 30;
	return (tl_len);
}

void	free_lexer_info(t_lexer_info **l_info)
{
	int	index;

	index = 0;
	while ((*l_info)->tokenized_line[index])
		free((*l_info)->tokenized_line[index++]);
	// free((*l_info)->line);//ここは後ほどmainと繋がってから
	free(*l_info);
	*l_info = NULL;
}

void	error_occuration_at_tokenize(t_lexer_info **l_info, bool is_syntax)
{
	free_lexer_info(l_info);
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

static void	take_pre_string(t_lexer_info *l_info)
{
	if (is_valid_pre_string(*(l_info->line_index), \
		l_info->line[(*(l_info->line_index)) - 1]))
	{
		l_info->tokenized_line[(*(l_info->tl_index))++] = \
			ft_substr(l_info->line, *(l_info->line_start_index), \
				*(l_info->line_index) - *(l_info->line_start_index));
		if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
			error_occuration_at_tokenize(&l_info, false);
	}
}

static void	take_last_string(t_lexer_info *l_info)
{
	char	last_token;

	take_pre_string(l_info);
	l_info->tokenized_line[*(l_info->tl_index)] = NULL;
	last_token = l_info->tokenized_line[(*(l_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '>' || last_token == '<')
		error_occuration_at_tokenize(&l_info, true);
	// free(line);//free_lexer_infoと同じくここも後ほど
	free(l_info);
}

static void	quote_separator(t_lexer_info *l_info)
{
	char	target;

	target = l_info->line[*(l_info->line_index)];
	(*(l_info->line_index))++;
	while (l_info->line[*(l_info->line_index)] && \
			l_info->line[*(l_info->line_index)] != target)
		(*(l_info->line_index))++;
	if (l_info->line[*(l_info->line_index)] != target)
		error_occuration_at_tokenize(&l_info, true);
	(*(l_info->line_index))++;
	l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, *(l_info->line_start_index), \
			*(l_info->line_index) - *(l_info->line_start_index));
	if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&l_info, false);
	*(l_info->line_start_index) = *(l_info->line_index);
}

static void	pipe_separator(t_lexer_info *l_info)
{
	char	last_token;

	take_pre_string(l_info);
	if (*(l_info->tl_index) == 0)
		error_occuration_at_tokenize(&l_info, true);
	last_token = l_info->tokenized_line[(*(l_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '<')//リダイレクトでも'>'こっち向きは実行できるっぽい
		error_occuration_at_tokenize(&l_info, true);
	l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, (*(l_info->line_index))++, 1);
	if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&l_info, false);
	*(l_info->line_start_index) = *(l_info->line_index);
}

static void	single_redirect_separator(t_lexer_info *l_info)
{
	char	last_token;
	
	take_pre_string(l_info);
	if (*(l_info->tl_index) != 0)
	{
		last_token = l_info->tokenized_line[(*(l_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
			error_occuration_at_tokenize(&l_info, true);
	}
	l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, (*(l_info->line_index))++, 1);
	if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&l_info, false);
	*(l_info->line_start_index) = *(l_info->line_index);
}

static	void	double_redirect_separator(t_lexer_info *l_info)
{
	char	last_token;

	take_pre_string(l_info);
	if (*(l_info->tl_index) != 0)
	{
		last_token = l_info->tokenized_line[(*(l_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
			error_occuration_at_tokenize(&l_info, true);
	}
	l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, *(l_info->line_index), 2);
	if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&l_info, false);
	*(l_info->line_index) += 2;
	*(l_info->line_start_index) = *(l_info->line_index);
}

static void	space_separator(t_lexer_info *l_info)
{
	take_pre_string(l_info);
	while (l_info->line[*(l_info->line_index)] == ' ')
		(*(l_info->line_index))++;
	*(l_info->line_start_index) = *(l_info->line_index);
}

static	bool is_quote(t_lexer_info *l_info)
{
	if (l_info->line[*(l_info->line_index)] == '\'' || \
		l_info->line[*(l_info->line_index)] == '"' )
			return (true);
	return (false);
}

static	bool is_single_redirect(t_lexer_info *l_info)
{
	if (l_info->line[*(l_info->line_index)] == '>' || \
		l_info->line[*(l_info->line_index)] == '<')
				return (true);
	return (false);
}

static	bool is_double_redirect(t_lexer_info *l_info)
{
	if (!ft_strncmp(&(l_info->line[*(l_info->line_index)]), ">>", 2) || \
		!ft_strncmp(&(l_info->line[*(l_info->line_index)]), "<<", 2))
			return (true);
	return (false);
}

static char **tokenize(t_lexer_info *l_info)
{
	char	**tokenized_line;
	int		tl_len;

	tl_len = tl_len_count(l_info->line);
	tokenized_line = (char **)ft_calloc(sizeof(char *), tl_len);
	l_info->tokenized_line = tokenized_line;
	while (l_info->line[*(l_info->line_index)])
	{
		if (l_info->line[*(l_info->line_index)] == ' ')
			space_separator(l_info);
		else if (l_info->line[*(l_info->line_index)] == '|')
			pipe_separator(l_info);
		else if (is_quote(l_info))
				quote_separator(l_info);
		else if (is_double_redirect(l_info))
			double_redirect_separator(l_info);
		else if (is_single_redirect(l_info))
			single_redirect_separator(l_info);
		else
			(*(l_info->line_index))++;
	}
	take_last_string(l_info);
	return (l_info->tokenized_line);
}

char	**tokenize_main(char *line)
{
	t_lexer_info	*l_info;
	int				line_index;
	int				line_start_index;
	char			**tokenized_line;
	int				tl_index;

	line_index = 0;
	line_start_index = 0;
	tl_index = 0;
	l_info = (t_lexer_info *)malloc(sizeof(t_lexer_info));
	l_info->line = line;
	l_info->line_index = &line_index;
	l_info->line_start_index = &line_start_index;
	l_info->tl_index = &tl_index;
	tokenized_line = tokenize(l_info);
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
