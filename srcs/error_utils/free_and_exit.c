/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 04:20:27 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"
#include <unistd.h>

void	free_and_exit(int status)
{
	free_all();
	exit(status);
}

void	free_all(void)
{
	destroy_garbage();
}

void	print_err_and_exit(char *err, int status, int erno)
{
	print_err(err, erno);
	free_and_exit(status);
}

void	handle_malloc_error(char *err)
{
	ft_putstr_fd(err, STDERR_FILENO);
	destroy_garbage();
	exit(EXIT_FAILURE);
}
