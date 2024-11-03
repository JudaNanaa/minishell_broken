/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:49:14 by madamou           #+#    #+#             */
/*   Updated: 2024/10/27 14:03:51 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "parsing.h"

void	ft_addhistory(char	*str);
char	*replace_aliases(char *cmd);
void add_to_queue(t_queue *queue, char *content, t_type type);
t_token *lexer_alias(t_data *data, char *command_line);
t_alias	*search_in_alias(char *key);
char	*ft_getalias(char *key);

int is_redirection_type(t_type type)
{
	if (type == HEREDOC || type == INFILE || type == OUT_APP
		|| type == OUT_TRUNC || type == HERESTRING)
		return (1);
	return (0);
}

void set_token_type(t_token *current, t_type type)
{
	t_token *tmp;

	if (type != CMD)
	{
		current->type = type;
		return ;
	}
	if (current->prev && is_redirection_type(current->prev->type))
		current->type = FILES;
	else if (type == CMD)
	{
		tmp = current->prev;
		while (tmp && is_operator_type(tmp->type) == false)
		{
			if (tmp->type == CMD)
			{
				current->type = ARG;
				break;
			}
			current->type = CMD;
			tmp = tmp->prev;
		}
	}
	if (current->type == CMD && ft_strchr(current->content, '=')
		&& is_a_good_variable(current->content))
		current->type = LOCAL_VAR;
}

int	check_aliases(t_token *token, t_queue *queue)
{
	char	*str;
	t_token	*alias;

	if (token->type != CMD)
		return (0);
	str = ft_getalias(token->content);
	if (str == NULL)
		return (0);
	if (token == queue->first)
		queue->first = NULL;
	else
	 	token->prev->next = NULL;
	queue->last = token->prev;
	alias = lexer_alias(get_data(NULL, GET), str);
	if (alias == NULL)
		return (EXIT_FAILURE);
	if (queue->last)
		queue->last->next = alias;
	else
	 	queue->first = alias;
	while (alias->next)
		alias = alias->next;
	queue->last = alias;
	return (0);
}

void add_to_queue(t_queue *queue, char *content, t_type type)
{
	t_token	*token;
	t_token	*current;

	token = ft_malloc(sizeof(t_token) * 1);
	if (token == NULL)
		handle_malloc_error("add to queue");
	ft_memset(token, 0, sizeof(t_token));
	if (queue->first == NULL)
		queue->first = token;
	token->prev = queue->last;
	if (queue->last)
		queue->last->next = token;
	queue->last = token;
	token->content = content;
	set_token_type(token, type);
	current = queue->first;
	while (current->next)
		current = current->next;
	current->next = token;
	token->next = NULL;
}

void add_queue_subshell(t_queue *queue, char *str, int *i)
{
	int	j;
	int	open_parenthesis;
	int	close_parenthesis;
	char	*cmd;

	j = 0;
	open_parenthesis = 1;
	close_parenthesis = 0;
	while (str[*i + ++j])
	{
		if (str[*i + j] == '(')
			open_parenthesis++;
		if (str[*i + j] == '"')
			continue_until_find(*i, &j, str, '"');
		if (str[*i + j] == '\'')
			continue_until_find(*i, &j, str, '\'');
		if (str[*i + j] == ')')
			close_parenthesis++;
		if (open_parenthesis - close_parenthesis == 0)
			break ;
	}
	if (!str[*i + j] && open_parenthesis -  close_parenthesis!= 0)
	{
		(*i += j);
		parse_err(")");
		queue->last = NULL;
		return;
	}
	cmd = ft_substr(str, *i + 1, j - 1);
	if (!cmd)
		handle_malloc_error("parenthesis");
	add_to_queue(queue, cmd, SUBSHELL);
	*i += j + 1;
}

int add_token(t_queue *queue, char *str, int *i)
{
	int j;
	char	*cmd;

	j = 0;
	while (str[*i + j] && !is_space(str[*i + j]) && !is_a_separator(&str[*i + j]))
	{
		if (str[*i + j] == '"')
			continue_until_find(*i, &j, str, '"');
		else if (str[*i + j] == '\'')
			continue_until_find(*i, &j, str, '\'');
		else if (str[*i + j] == '{')
			continue_until_find(*i, &j, str, '}');
		j++;
	}
	cmd = ft_substr(str, *i, j);
	if (!cmd)
		handle_malloc_error("add token");
	if (!cmd[0] && !is_a_quotes(str[*i + j - 1]))
		return (*i += j, 0);
	add_to_queue(queue, cmd, CMD);
	*i += j;
	return (0);
}

int check_pipe(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "||") == 0)
		return (OR);
	parse_err("||");
	return (U_TOKEN);	
}

int check_outfile(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (OUT_TRUNC);
	if (ft_strcmp(token, ">>") == 0)
		return (OUT_APP);
	parse_err(">>");
	return (U_TOKEN);
}

int check_and(char *token)
{
	if (ft_strcmp(token, "&&") == 0)
		return (AND);
	if (ft_strcmp(token, "&") == 0)
		parse_err("&");
	else
		parse_err("&&");
	return (U_TOKEN);
}

int check_infile(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (INFILE);
	if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(token, "<<<") == 0)
		return (HERESTRING);
	parse_err("<<<");
	return (U_TOKEN);
}

int	assigne_type(char *redirection)
{
	if (ft_strncmp(redirection, "|", 1) == 0)
		return (check_pipe(redirection));
	if (ft_strncmp(redirection, ">", 1) == 0)
		return (check_outfile(redirection));
	if (ft_strncmp(redirection, "<", 1) == 0)
		return (check_infile(redirection));
	if (ft_strncmp(redirection, "&", 1) == 0)
		return (check_and(redirection));
	if (ft_strncmp(redirection, "\n", 1) == 0)
		return (LIST);
	if (ft_strcmp(redirection, ";") == 0)
		return (LIST);
	else
		parse_err(";;");
	return (U_TOKEN);
}

void add_metachars(t_queue *queue, char *str, int *i)
{
	char	*redirection;
	char	symbol;
	int		type;
	int		j;

	symbol = str[*i];
	j = 0;
	while (str[*i + j] == symbol)
		j++;
	redirection = ft_malloc(sizeof(char) * (j + 1));
	if (!redirection)
		handle_malloc_error("redirections");
	j = -1;
	while (str[*i + ++j] == symbol)
		redirection[j] = str[*i + j];
	redirection[j] = '\0';
	type = assigne_type(redirection);
	if (type == U_TOKEN)
	{
		queue->last = NULL;
		return ;
	}
	add_to_queue(queue, redirection, type);
	*i += j;
}

void	add_elem(t_queue *queue, char *str, int *i)
{
	if (str[*i] == '(')
	{
		add_queue_subshell(queue, str, i);
	}
	else if (is_a_separator(&str[*i]))
		add_metachars(queue, str, i);
	else
		add_token(queue, str, i);
}

int only_whitespace(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_space(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

t_token *lexer(t_data *data, char *command_line)
{
	int			i;
	char		*tmp;
	t_queue	queue;

	i = 0;
	queue.first = NULL;
	queue.last = NULL;
	tmp = ft_strdup(command_line);
	command_line = check_if_command_line_is_good(data, command_line);
	if (!command_line)
		return (ft_addhistory(tmp), NULL);
	ft_free(tmp);
	ft_addhistory(command_line);
	if (data->is_child == true && only_whitespace(command_line) == true)
	{
		parse_err(")");
		free_and_exit(2);
	}
	while (command_line[i])
	{
		skip_white_space(command_line, &i);
		if (command_line[i])
		{
			add_elem(&queue, command_line, &i);
			if (check_aliases(queue.last, &queue) == EXIT_FAILURE)
				queue.last = NULL;
		}
		if (queue.last == NULL)
			return (NULL);
	}
	return (queue.first);
}

t_token *lexer_alias(t_data *data, char *command_line)
{
	int			i;
	char		*tmp;
	t_queue	queue;

	i = 0;
	queue.first = NULL;
	queue.last = NULL;
	tmp = ft_strdup(command_line);
	command_line = check_if_command_line_is_good(data, command_line);
	if (!command_line)
		return (NULL);
	ft_free(tmp);
	if (data->is_child == true && only_whitespace(command_line) == true)
	{
		parse_err(")");
		free_and_exit(2);
	}
	while (command_line[i])
	{
		skip_white_space(command_line, &i);
		if (command_line[i])
			add_elem(&queue, command_line, &i);
		if (queue.last == NULL)
			return (NULL);
	}
	return (queue.first);
}
