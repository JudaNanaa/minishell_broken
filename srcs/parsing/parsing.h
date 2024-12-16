/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:53:32 by madamou           #+#    #+#             */
/*   Updated: 2024/10/09 01:39:8 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

// #include "../../includes/includes.h"
#include "../data/data.h"

// Before Parsing
# define NEWLINE1 "\n"
# define SPACE1 " "
# define SEMICOLON "; "
# define S_U_EOF "minishell: unexpected EOF while looking for matching `''"
# define D_U_EOF "minishell: unexpected EOF while looking for matching `\"'"

char	*check_if_command_line_is_good(t_data *data, char *str);

# define false 0
# define true 1


typedef enum
{
	CMD,
	ARG,
	PIPE,
	AND,
	OR,
	LIST,
	HEREDOC,
	HERESTRING,
	INFILE,
	OUT_APP,
	OUT_TRUNC,
	FILES,
	SUBSHELL,
	LOCAL_VAR,
	U_TOKEN,
}t_type;

typedef struct s_file
{
	t_type mode;
	char **heredoc_content;
	int expand_heredoc;
	char *path;
	struct s_file *next;
} t_file;

typedef struct s_token
{
	char *content;
	t_type type;
	char **args;
	t_file *files;
	struct s_token *next;
	struct s_token *prev;
	struct s_token *left;
	struct s_token *right;
} t_token;

typedef struct s_queue
{
	t_token *first;
	t_token *last;
} t_queue;

// Heredoc
int	get_heredoc(t_file *neww);

// Lexing
t_token *lexer(t_data *data, char *command_line);

// Parser
int	parser(t_queue *queue);
int	parse_err(char *token);


// Ast
t_token *create_ast(t_token *first, int weight);
t_token *create_ast_test(t_token *first);


// Utils
int	is_a_separator(char *c);
int	is_space(char c);
void	continue_until_find(int i, int *j, char *str, char to_find);
int	is_a_quotes(char c);
int is_redirection_type(t_type type);
int is_operator_type(t_type type);
int remove_quotes(char *str);
char **expand(char **args);
char *expand_str(char *str);


#endif