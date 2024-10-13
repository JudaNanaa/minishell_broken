/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:24:15 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 04:08:58 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
#define DATA_H

// #include "../../includes/includes.h"
# include "../environement/env.h"

typedef struct s_data
{
	char *name;
	t_env *env;
	int status;
	int is_child;
	int signaled;
}t_data;

// set and get data
# define SET 0
# define GET 1

// is chil or no
# define NO 0
# define YES 1
t_data *get_data(t_data *data, int flag);

#endif