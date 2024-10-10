/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:34:36 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 04:33:41 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb_utils.h"

/*
Clear the garbage collector:
free() all the addresses allocated by ft_malloc() function
don't free the addresses locked by lock() function
*/
void	clear_garbage(void)
{
	t_garbage	*garbage;
	t_garb_node	*node;
	t_garb_node	*temp;

	garbage = get_garbage(NULL, GETTER);
	if (garbage == NULL)
		return ;
	node = garbage->first;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (temp->locked == false)
			destroy_garbage_node(temp, garbage);
	}
}

/*
lock the addresse if allocated by ft_malloc() function,
the clear_garbage() function don't free() the locked adresses.
the desrtoy_garbage() function does free the locked addresses
*/
void	lock(void *address)
{
	t_garb_node	*node;
	t_garbage	*garbage;

	if (address == NULL)
		return ;
	garbage = get_garbage(NULL, GETTER);
	if (garbage == NULL)
		return ;
	node = find_by_address(address, garbage);
	if (node == NULL)
		return ;
	node->locked = true;
}

/*
unlock the addresse if allocated by ft_malloc() function,
the clear_garbage() function can't free() the locked adresses.
*/
void	unlock(void *address)
{
	t_garb_node	*node;
	t_garbage	*garbage;

	if (address == NULL)
		return ;
	garbage = get_garbage(NULL, GETTER);
	if (garbage == NULL)
		return ;
	node = find_by_address(address, garbage);
	if (node == NULL)
		return ;
	node->locked = false;
}
