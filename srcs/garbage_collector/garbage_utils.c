/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 03:32:37 by madamou           #+#    #+#             */
/*   Updated: 2024/12/15 03:55:55 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include <stdbool.h>
#include <time.h>

t_garbage	*get_garbage(void)
{
	static t_garbage	save;

	return (&save);
}

void	add_back_garbage(t_garbage_elem *elem)
{
	t_garbage		*garbage;
	t_garbage_elem	*tmp;

	garbage = get_garbage();
	if (garbage->first == NULL)
		garbage->first = elem;
	else
	{
		tmp = garbage->first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->prev = tmp;
	}
}

int	create_node_garbage(void *ptr)
{
	t_garbage_elem	*new;

	new = malloc(sizeof(t_garbage_elem));
	if (new == NULL)
		return (free(ptr), -1);
	new->lock = false;
	new->prev = NULL;
	new->next = NULL;
	new->ptr = ptr;
	add_back_garbage(new);
	return (0);
}

bool	is_in_garbage(void *ptr)
{
	t_garbage		*gargabe;
	t_garbage_elem	*tmp;

	gargabe = get_garbage();
	tmp = gargabe->first;
	while (tmp)
	{
		if (tmp->ptr == ptr)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	destroy_garbage_node(void *ptr)
{
	t_garbage_elem	*current;
	t_garbage		*garbage;

	garbage = get_garbage();
	current = garbage->first;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (current->prev == NULL)
				garbage->first = current->next;
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(ptr);
			free(current);
			break ;
		}
		current = current->next;
	}
}
