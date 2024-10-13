/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_moussa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 02:10:17 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 03:0308 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include <sys/types.h>
#include <term.h>

t_token *create_ast_right(t_token *first, t_type type_return);

int get_weight(t_type type)
{
	if (type == PIPE)
		return (0);
	if (type == AND || type == OR)
		return (1);
	if (type == LIST)
		return (2);
	return (-1);
}

t_token *get_next_operator(t_token *summit)
{
	while (summit->right)
	{
		summit = summit->right;
	}
	return (summit->next);
}

t_token *recursive_ast_right(t_token *current, t_token *tokens, t_type to_stop)
{
	t_token *operator;

	if (tokens == NULL || get_weight(to_stop) <= get_weight(tokens->type))
		return (current);
	operator = current;
	if (get_weight(current->type) > get_weight(tokens->type))
		operator->right = create_ast_right(tokens->prev, current->type);
	else
	{
		operator = tokens;
		operator->right = operator->next;
		operator->left = current;
	}
	return (recursive_ast_right(operator, get_next_operator(operator), to_stop));
}

t_token *create_ast_right(t_token *first, t_type type_return)
{
	t_token *operator;

	if (!first->next || !first->next->next)
		return (first);
	operator = first->next;
	operator->left = first;
	operator->right = operator->next;
	return (recursive_ast_right(operator, operator->next->next, type_return));
}

t_token *recursive_ast(t_token *current, t_token *tokens)
{
	t_token *operator;

	if (tokens == NULL)
		return (current);
	operator = current;
	if (get_weight(current->type) > get_weight(tokens->type))
		operator->right = create_ast_right(tokens->prev, current->type);
	else
	{
		operator = tokens;
		operator->right = operator->next;
		operator->left = current;
	}
	return (recursive_ast(operator, get_next_operator(operator)));
}

t_token *create_ast_test(t_token *first)
{
	t_token *operator;

	if (!first->next || !first->next->next)
		return (first);
	operator = first->next;
	operator->left = first;
	operator->right = first->next->next;
	return (recursive_ast(operator, operator->next->next));
}
