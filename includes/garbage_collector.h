/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:31:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 04:36:11 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_garb_node
{
	void					*address;
	struct s_garb_node		*next;
	unsigned long			size;
	bool					locked;
}							t_garb_node;

typedef struct s_garbage
{
	t_garb_node				*first;
}							t_garbage;

void	*ft_malloc(unsigned long size);
void	*ft_realloc(void *ptr, unsigned long size_to_add);
void	ft_free(void *address);
void	destroy_garbage(void);
void	clear_garbage(void);
void	lock(void *address);
void	unlock(void *address);

#endif