/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:57:30 by madamou           #+#    #+#             */
/*   Updated: 2024/11/29 00:46:28 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:57:30 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 15:59:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/includes.h"
#include "parsing.h"
#include <readline/history.h>
#include <unistd.h>

int	parse_err(char *token)
{
	t_data *data;
	
	data = get_data(NULL, GET);
	replace_newline(token);
	ft_fprintf(STDERR_FILENO, "%s: syntax error near unexpected token `", data->name);
	if (token != NULL)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	data->status = 2;
	return (EXIT_FAILURE);
}

int is_operator_type(t_type type)
{
	if (type == AND || type == OR || type == PIPE || type == LIST)
		return (true);
	return (false);
}

void	token_to_queue(t_queue *queue, t_token *token)
{
	token->prev = queue->last;
	if (queue->first == NULL)
		queue->first = token;
	if (queue->last)
		queue->last->next = token;
	queue->last = token;
}

void set_command_args(t_token *current)
{
	t_token *tmp;
	int len;
	
	len = 0;
	tmp = current;
	while (tmp && is_operator_type(tmp->type) == false)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			len++;
		tmp = tmp->next;
	}
	current->args = ft_malloc(sizeof(char *) * (len + 1));
	if (current->args == NULL)
		handle_malloc_error("parsing");
	tmp = current;
	len = 0;
	while (tmp && is_operator_type(tmp->type) == false)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			current->args[len++] = tmp->content;
		tmp = tmp->next;
	}
	current->args[len] = NULL;
}

void add_back_files(t_file **files, t_file *to_add)
{
	t_file *buff;
	
	buff = *files;
	if (buff == NULL)
		*files = to_add;
	else
	{
		while (buff->next)
			buff = buff->next;
		buff->next = to_add;
	}
}

int add_redirections(t_token *redir, t_queue *queue)
{
	t_file *new;

	if (redir->next == NULL)
		return (parse_err(NULL), EXIT_FAILURE);
	if (is_redirection_type(redir->next->type))
	{
		if (redir->next->next)
			return (parse_err(redir->next->content), EXIT_FAILURE);
		return (parse_err(NULL), EXIT_FAILURE);
	}
	if (redir->next->type == SUBSHELL)
		return (parse_err("("), EXIT_FAILURE);
	new = ft_malloc(sizeof(t_file));
	if (new == NULL)
		handle_malloc_error("parsing");
	new->mode = redir->type;
	new->path = redir->next->content;
	new->heredoc_content = NULL;
	new->next = NULL;
	if (new->mode == HEREDOC || new->mode == HERESTRING)
	{
		if (get_heredoc(new) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	add_back_files(&queue->last->files, new);
	return (EXIT_SUCCESS);
}

int	add_command(t_token *command, t_queue *queue)
{
	if (queue->last->type == SUBSHELL)
		return (parse_err(command->content));
	set_command_args(command);
	queue->last->args = command->args;
	queue->last->content = command->content;
	queue->last->type = CMD;
	return (EXIT_SUCCESS);
}

char *get_command_subshell(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// Si str == vide faire un readline une fois et faire la function
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i + j] && !is_space(str[i + j]) && !is_a_separator(&str[i + j]))
		j++;
	str[i + j] = '\0';
	return (&str[i]);
}

int	add_subshell(t_token *subshell, t_queue *queue)
{
	if (queue->last->type == CMD)
		return (parse_err(get_command_subshell(subshell->content)));
	queue->last->content = subshell->content;
	queue->last->type = SUBSHELL;
	return (EXIT_SUCCESS);
}

int	fill_queue(t_token *current, t_queue *queue)
{
	while (current)
	{
		if (is_operator_type(current->type))
				return (parse_err(current->content));
		token_to_queue(queue, current);
		while (current != NULL && is_operator_type(current->type) == false)
		{
			if (is_redirection_type(current->type))
			{
				if (add_redirections(current, queue) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				current = current->next->next;
				queue->last->next = NULL;
				continue;
			}
			else if (current->type == CMD)
				add_command(current, queue);
			else if (current->type == SUBSHELL)
			{
				if (add_subshell(current, queue) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (current->type == ARG)
				queue->last->next = NULL;
			current = current->next;
		}
		if (current == NULL)
			break ;
		token_to_queue(queue, current);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	parser(t_queue *queue)
{
	t_token	*current;

	current = queue->first;
	ft_memset(queue, 0, sizeof(t_queue));
	if (fill_queue(current, queue) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_operator_type(queue->last->type) && queue->last->type != LIST)
		return (parse_err(queue->last->content));
	return (EXIT_SUCCESS);
}
