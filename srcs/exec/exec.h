/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:29 by madamou           #+#    #+#             */
/*   Updated: 2024/10/12 00:13:21 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include "../../includes/includes.h"

void start_exec(t_token *node);
void exec(t_token *current);

// Operators
void exec_or(t_token *node);
void exec_and(t_token *node);
void exec_pipe(t_token *node);
void exec_list(t_token *node);


// Utils
int ft_fork(void);
int open_files(t_token *node);
int	check_built_in(char *command);
void	exit_status(int status);
char	*expand_line(char *line);
int	is_a_var_char(char c);
char	*expand_if_necessary(char *str);


#endif