/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:26:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 01:53:08 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb_utils.h"

t_garb_node	*find_by_address(void *address, t_garbage *garbage)
{
	t_garb_node	*node;

	node = garbage->first;
	while (node != NULL)
	{
		if (node->address == address)
			return (node);
		node = node->next;
	}
	error_log("find_by_address: address not found", false);
	return (NULL);
}

t_garb_node	*find_before_node(t_garb_node *node, t_garbage *garbage)
{
	t_garb_node	*before_node;

	if (node == garbage->first)
		return (NULL);
	before_node = garbage->first;
	while (before_node != NULL)
	{
		if (before_node->next == node)
			return (before_node);
		before_node = before_node->next;
	}
	error_log("find_before_node: address not found", false);
	return (NULL);
}

int	init_static(t_garbage **_static, void *arg)
{
	if (arg == NULL)
		return (EXIT_FAILURE);
	*_static = (t_garbage *)arg;
	return (EXIT_SUCCESS);
}

int	is_destroyed(bool setter, bool value)
{
	static int	is_destroy = NOT_DEFINED;

	if (setter == true)
		is_destroy = value;
	return (is_destroy);
}

t_garbage	*get_garbage(t_garbage *garb, bool setter)
{
	static t_garbage	*garbage = NULL;

	if (setter == READER)
		return (garbage);
	garbage = garb;
	return (NULL);
}
