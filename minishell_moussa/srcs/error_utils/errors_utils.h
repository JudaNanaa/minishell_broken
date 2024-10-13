/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:38 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 22:39:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_UTILS_H
# define ERRORS_UTILS_H

// # include "../../includes/includes.h"
# include <stdbool.h>
# include "../../includes/garbage_collector.h"
# include "../../libft/libft.h"

char	*ft_re_strjoin(const char *s1, const char *s2);

# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

void	free_and_exit(int status);
void	ft_close(int *fd);
void	free_all(void);
void	print_err(char *err, int erno);
void	print_err_and_exit(char *err, int status, int erno);
void	_err(char *token);
void	error_log(char *error, int erno);
void	built_in_error(char *function, char *error, int erno);
char	*replace_newline(char *str);
void	handle_malloc_error(char *err);

#endif