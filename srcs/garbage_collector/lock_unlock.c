/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 03:34:14 by madamou           #+#    #+#             */
/*   Updated: 2024/12/15 03:35:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

void	lock(void *ptr)
{
	t_garbage_elem	*current;
	t_garbage		*garbage;

	garbage = get_garbage();
	current = garbage->first;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->lock = true;
			return ;
		}
		current = current->next;
	}
}

void	unlock(void *ptr)
{
	t_garbage_elem	*current;
	t_garbage		*garbage;

	garbage = get_garbage();
	current = garbage->first;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->lock = false;
			return ;
		}
		current = current->next;
	}
}
