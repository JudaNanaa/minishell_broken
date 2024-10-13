/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:26:02 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/11 22:34:42 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb_utils.h"

t_garb_node	*find_in_garbage(void *address, t_garbage *garbage)
{
	t_garb_node	*garb_node;

	garb_node = garbage->first;
	while (garb_node != NULL)
	{
		if (garb_node->address == address)
			return (garb_node);
		garb_node = garb_node->next;
	}
	return (NULL);
}

t_garbage	*init_garbage(void)
{
	t_garbage	*garbage;

	garbage = malloc(sizeof(t_garbage) * 1);
	if (garbage == NULL)
		return (handle_malloc_error("init_garbage"), NULL);
	garbage->first = NULL;
	is_destroyed(SETTER, false);
	get_garbage(garbage, SETTER);
	ft_free(NULL);
	destroy_garbage();
	ft_realloc(NULL, 0);
	return (garbage);
}

void	destroy_garbage_node(t_garb_node *node_to_destroy, t_garbage *garb)
{
	t_garb_node	*node;

	node = find_before_node(node_to_destroy, garb);
	if (node == NULL)
		garb->first = node_to_destroy->next;
	else
		node->next = node_to_destroy->next;
	free(node_to_destroy->address);
	free(node_to_destroy);
}

int	new_garb_node(void *address, t_garbage *garbage, unsigned long size)
{
	t_garb_node	*new_node;

	new_node = malloc(sizeof(t_garb_node) * 1);
	if (new_node == NULL)
		return (error_log("new_garb_node: malloc() failed:", true),
			EXIT_FAILURE);
	new_node->address = address;
	new_node->size = size;
	new_node->next = garbage->first;
	new_node->locked = false;
	garbage->first = new_node;
	return (EXIT_SUCCESS);
}
