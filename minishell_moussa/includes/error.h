/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:17:53 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 06:04:21 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#include "includes.h"

int		errcode(int errcode, bool setter);
void	free_all(void);
void	print_err(char *err, bool erno);
void	print_err_and_exit(char *err, int status, bool erno);
void	parse_err(char *error, char *token);
void	init_error_log(void);
// void	error_log(char *error, bool erno);
void	malloc_failed(char *function);
void	free_and_exit(int status);

#endif