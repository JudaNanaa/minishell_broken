/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/11 23:46:53 by ibaby            ###   ########.fr       */
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
	ft_putendl_fd(err, STDERR_FILENO);
	destroy_garbage();
	exit(EXIT_FAILURE);
}
