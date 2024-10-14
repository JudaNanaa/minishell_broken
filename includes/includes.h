
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:17:14 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/13 17:52:36 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

// # include "error.h"

# include <stdbool.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include "../srcs/environement/env.h"
# include "../srcs/wildcard/wildcard.h"
# include "../srcs/data/data.h"
# include "../srcs/error_utils/errors_utils.h"
# include "../srcs/environement/env.h"
# include "../libft/libft.h"
# include "../srcs/signal/signal.h"
# include "../srcs/builtins/builtins.h"
# include "../srcs/utils/utils.h"
# include "garbage_collector.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/minishell_loop/minishell_loop.h"
# include "../srcs/features/features.h"
# include "../srcs/exec/exec.h"

extern volatile sig_atomic_t	g_signal;

#endif