/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:25:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 05:13:32 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURES_H
# define FEATURES_H

#include "../../includes/includes.h"

# define ALIAS ".alias"
# define MAX_ALIAS 128
# define HISTORY_FILE "/tmp/.history"
# define ALIAS_USAGE "alias: usage: abc=xyz"
# define MINISHELL_PROMPT "\001\033[36;1m\002minishell \001\033[0m\002 "

char	***get_alias(char ***init_alias);
int		check_if_alias(void *data, char ***aliases);
int		init_aliases(void);
char	***search_aliases(int fd);
char	**line_to_alias(char *line);
void	clear_3d_array(char ***alias, int end);
char	***get_alias(char ***init_alias);
char	**add_alias(char **array, char *line, int start);
char	**insert_alias(char **command, char **alias);
char	*get_last_history(char *str, bool set);
void	add_and_save(char *str);
char	*add_git_head(char *prompt);
char	*add_dir_name(char *prompt);
char	*git_line(char *git_file);
char	*add_git_delay(char *prompt);
char	*git_head(void);
int		is_delayed(char *head);
char	*add_arrow(void);
char	*urgency_prompt(void);

#endif