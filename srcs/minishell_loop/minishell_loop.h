/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:19:50 by madamou           #+#    #+#             */
/*   Updated: 2024/10/14 23:51:48 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LOOP_H
#define MINISHELL_LOOP_H

// #include "../../includes/includes.h"
# include "../data/data.h"

# define CLR "\001\033[0;34m\002"
# define ND "[0;31m$\001\033[0m\002"
# define MSHRC ".mshrc"

void loop_minishell(t_data *data);
void subshell_routine(t_data *data, char *command_line);

#endif