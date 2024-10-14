/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:03:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/14 14:07:54 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../../includes/includes.h"
# include <dirent.h>

typedef struct s_path
{
	char			*path;
	struct s_path	*next;
}	t_path;

typedef struct s_wildcard
{
	char	*complete_path;
	char	*start_path;
	bool	dir;
	bool	absolute;
	t_path	*paths;
}	t_wildcard;

# define DIRR 0

typedef struct s_wildcard_moussa
{
	char	*base_path;
	char	**to_expand;
	bool	dir;
} t_wildcard_moussa;

typedef struct s_wcards
{
	char			*content;
	struct s_wcards	*before;
	struct s_wcards	*next;
}					t_wcards;


// Moussa
void				create_node_wcards(t_wcards **wcards, char *str, int i,
						int j);
void				skip_quote_wcards(char *str, int i, int *j);
int					ft_strncmp_reverse(char *s1, char *s2, int len_s2);
char **expand_wildcards(char *to_expand);


// Idissa
bool	is_final_file(struct dirent *file, t_wildcard *wildcard);
int		is_valid_file(struct dirent *file, t_wildcard *wildcard);
int		is_valid_name(char *name, char *original);
char	**paths_to_tab(t_path *paths);
t_path	*replace_wildcard(t_wildcard *wildcard);
void	get_start_path(char *path, t_wildcard *wildcard);
char	*complete_path(char **path, int depth, bool absolute, bool dir);
char	*actual_path(char **path, int depth, bool absolute, bool dir);

#endif
