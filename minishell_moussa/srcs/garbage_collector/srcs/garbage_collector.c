/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:25:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/11 22:34:48 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb_utils.h"

/*	this function works like the real malloc function,
	it returns a pointers to an heap allocated zone.
	Make sure to use this function at least one time before
	the other functions.*/
void	*ft_malloc(unsigned long size)
{
	static t_garbage	*garbage = NULL;
	void				*ptr;

	if (is_destroyed(READER, false) == NOT_DEFINED)
		is_destroyed(SETTER, false);
	if (is_destroyed(READER, false) == true)
		return (NULL);
	if (garbage == NULL)
	{
		garbage = init_garbage();
		if (garbage == NULL)
			return (NULL);
	}
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	if (new_garb_node(ptr, garbage, size) == EXIT_FAILURE)
		return (free(ptr), NULL);
	return (ptr);
}

void	*ft_realloc(void *ptr, unsigned long size_to_add)
{
	static t_garbage	*garbage = NULL;
	t_garb_node			*ptr_node;
	unsigned char		*new_ptr;

	if (garbage == NULL)
		return (garbage = get_garbage(NULL, false), NULL);
	if (is_destroyed(READER, false) != false)
		return (NULL);
	if (ptr == NULL)
		return (ft_calloc(1, size_to_add));
	if (size_to_add == 0)
		return (ptr);
	ptr_node = find_by_address(ptr, garbage);
	if (ptr_node == NULL)
		return (NULL);
	new_ptr = ft_calloc(1, ptr_node->size + size_to_add);
	if (new_ptr == NULL)
		return (ft_free(ptr), NULL);
	ft_memcpy(new_ptr, ptr, ptr_node->size);
	return ((void *)new_ptr);
}

/*this function copy the real 'free( )' function.
You can use it on all addresses, 
whether they are allocated by the 'ft_malloc( )' function or not.*/
void	ft_free(void *address)
{
	static t_garbage	*garbage = NULL;
	t_garb_node			*node_to_free;

	if (address == NULL)
		return ;
	if (is_destroyed(READER, false) != false)
		return ;
	if (garbage == NULL)
		return (garbage = get_garbage(NULL, GETTER), (void)0);
	node_to_free = find_by_address(address, garbage);
	if (node_to_free == NULL)
		return ;
	destroy_garbage_node(node_to_free, garbage);
	return ;
}

/*this function free the garbage and all the addresses allocated
by 'ft_malloc( )' but not freed by 'ft_free( )'.
Use it with a NULL parameter.
Make sure to use this function at the very end, because the others
functions are disabled after that.*/
void	destroy_garbage(void)
{
	static t_garbage	*garbage = NULL;
	t_garb_node			*node;
	t_garb_node			*temp;

	if (is_destroyed(READER, false) != false)
		return ;
	if (garbage == NULL)
	{
		garbage = get_garbage(NULL, GETTER);
		return ;
	}
	node = garbage->first;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		destroy_garbage_node(temp, garbage);
	}
	free(garbage);
	is_destroyed(SETTER, true);
}
