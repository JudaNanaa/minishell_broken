/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:25:56 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 04:43:20 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARB_UTILS_H
# define GARB_UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include "../../../includes/garbage_collector.h"
# include "../../../libft/libft.h"
# include "../../error_utils/errors_utils.h"

# define MALLOC_FAILED "syscall: malloc failed"

# define E1 "Error: use ft_malloc before any other garbage_collector functions"
# define E2 "Error: can't use an garbage function after using destroy_garbage()"
# define E3 "Error: use of ft_free on an address non allocated by ft_malloc()"
# define WRITE_ERROR "Error: garbage_collector: write function failed"
# define NOT_DEFINED 3
# define SETTER 1
# define READER 0
# define GETTER 0

t_garb_node	*find_in_garbage(void *address, t_garbage *garbage);
int			new_garb_node(void *address, t_garbage *garbage,
				unsigned long size);
void		destroy_garbage_node(t_garb_node *node, t_garbage *garbage);
t_garbage	*init_garbage(void);
// void		print_err(char *error, bool erno);
t_garb_node	*find_by_address(void *address, t_garbage *garbage);
t_garb_node	*find_before_node(t_garb_node *node, t_garbage *garbage);
// void		error_log(char *error, bool erno);
int			init_static(t_garbage **_static, void *arg);
int			is_destroyed(bool setter, bool value);
t_garbage	*get_garbage(t_garbage *garb, bool setter);

#endif