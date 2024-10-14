/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:56:49 by madamou           #+#    #+#             */
/*   Updated: 2024/10/14 16:52:40 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include <sys/types.h>
#include <term.h>

t_token *create_ast(t_token *first, int weight);

int	operator_weight(t_token *operator)
{
	if (operator->type == AND)
		return (2);
	if (operator->type == OR)
		return (2);
	if (operator->type == LIST)
		return (1);
	if (operator->type == PIPE)
		return (3);
	return (-1);
}

int	next_operator_weight(t_token *current)
{
	current = current->next;
	while (current && is_operator_type(current->type) == false)
		current = current->next;
	if (current == NULL)
		return (-1);
	return (operator_weight(current));
}

t_token	*ast_top(t_token *current)
{
	while (current->prev != NULL)
	{
		current = current->prev;
	}
	return  (current);
}

t_token	*next_operator(t_token *ast)
{
	t_token	*current;

	// current = ast_top(ast);
	current = ast;
	while (current->right)
	{
		current = current->right;
	}
	return (current->next);
}

t_token	*add_next_pyramid(t_token *left, t_token *operator, int weight)
{
	if (operator == NULL || weight >= operator_weight(operator))
		return (NULL);
	operator->left = left;
	left->prev = operator;
	operator->prev = NULL;
	if (operator_weight(operator) < next_operator_weight(operator))
	{
		operator->right = create_ast(operator->next, operator_weight(operator));
	}
	else
	{
		operator->right = operator->next;
	}
	if (operator->right->prev != NULL)
		operator->right->prev = operator;
	add_next_pyramid(operator, next_operator(operator), weight);
	return (operator);
}

t_token *create_ast(t_token *first, int weight)
{
	if (first->next == NULL)
		return (first);
	add_next_pyramid(first, first->next, weight);
	return (ast_top(first));
}
