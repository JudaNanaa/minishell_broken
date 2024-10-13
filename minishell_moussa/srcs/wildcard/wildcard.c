/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:03:35 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/14 00:15:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*reduce_slash(char *cmd)
{
	char	*str;
	int		i;

	str = ft_malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (str == NULL)
		handle_malloc_error("reduce slash");
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			while (cmd[i + 1] == '/')
				++i;
		str[i] = cmd[i];
	}
	str[i] == '\0';
	str = ft_re_strdup(str);
	if (str == NULL)
		handle_malloc_error("reduce slash");
	return (str);
}

bool	have_to_expand_wildcards(char *arg)
{
	
	if (ft_strchr(arg, '*') == NULL)
		return (false);
	if (ft_strchr(arg, ' ') || ft_strchr(arg, '\t'))
		return (false);
	if (0 /* is in quotes */)
		return (false);
	return (true);
}

t_path	*search_paths(char *path)
{
	t_wildcard	wildcard;

	ft_memset(&wildcard, 0, sizeof(t_wildcard));
	if (path[0] == '/')
		wildcard.absolute = true;
	else
		path = ft_strjoin("./", path);
	if (path[ft_strlen(path) - 1] == '/')
	{
		wildcard.dir = true;
		path[ft_strlen(path) - 1] = '\0';
	}
	wildcard.complete_path = path;
	get_start_path(path, &wildcard);
	replace_wildcard(&wildcard);
}

int	expand_wildcard(t_token *cmd)
{
	int			i;
	char		**new_args;

	i = -1;
	while (cmd->args[++i] != NULL)
	{
		if (have_to_expand_wildcards(cmd->args[i]) == false)
		{
			add_string_char_2d(&new_args, cmd->args[i]);
			continue ;
		}
		new_args = re_str2djoin(new_args, path_to_tab(search_paths(cmd->args[i])));
	}
}

t_path	*next_depth(struct dirent *file, t_wildcard *wildcard)
{
	char	*path;

	path = ft_strjoin(wildcard->complete_path, file->d_name);
	if (wildcard->dir == true)
		path = ft_re_strjoin(path, "/");
	return (search_paths(path));
}

void	add_path(t_path *paths, t_path **list)
{
	t_path	*curr;

	if (*list == NULL)
	{
		*list = paths;
		return;
	}
	curr = *list;
	while (curr->next)
		curr = curr->next;
	curr->next = paths;
}

t_path	*replace_wildcard(t_wildcard *wildcard)
{
	struct dirent	*file;
	DIR				*dir;
	t_path			*list;
	int				tmp;

	list = NULL;
	dir = opendir(wildcard->start_path);
	// if (dir == true && is_final_path(path, depth, absolute, dir));
		// return (actual_path(path, depth, absolute, dir));
	file = readdir(dir);
	while (file != NULL)
	{
		tmp = is_valid_file(file, wildcard);
		if (tmp == false)
		{
			file = readdir(dir);
			continue ;
		}
		else if (tmp == true)
			add_path(file_path(file, wildcard), &list);
		else
			add_path(next_depth(file, wildcard), &list);
		file = readdir(dir);
	}
}
