/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:56:17 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/14 00:15:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_path	*file_path(struct dirent file, t_wildcard *wildcard)
{
	t_path	*node;
	char	*path;

	path = ft_strdup(file->d_name);
	if (wildcard->dir == true)
		path = ft_re_strjoin(path, "/");
	node = ft_malloc(sizeof(t_path));
	node->next
}

bool	is_final_file(struct dirent *file, t_wildcard *wildcard)
{
	if (is_valid_file(file, wildcard) == true)
		return (true);
	else
		return (false);
}

bool	is_hidden(char *name, t_wildcard *wildcard)
{
	char	**tmp;

	tmp = ft_split(wildcard->complete_path, "/");
	tmp = &tmp[ft_strlen_2d(ft_split(wildcard->start_path, "/"))];
	while (ft_strchr(*tmp, '*') == NULL)
	{
		tmp = &tmp[1];
	}
	if (tmp == NULL)
		return (true);
	if (tmp[0][0] == '.' && name[0] == '.')
		return (true);
	if (tmp[0][0] != '.' && name[0] != '.')
		return (true);
	return (false);
}

int	is_valid_file(struct dirent *file, t_wildcard *wildcard)
{
	char	*actual_tmp;

	if (is_hidden(file->d_name, wildcard) == false)
		return (false);
	actual_tmp = ft_strjoin(wildcard->start_path, file->d_name);
	if (wildcard->dir == true && file->d_type != DT_DIR)
		return (false);
	return (is_valid_name(actual_tmp, wildcard->complete_path));
}

int	is_valid_name(char *name, char *original)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (is_hidden(name, original) == false)
		return (false);
	while (original[i] != '\0' && name[j] != '\0')
	{
		if (original[i] == '*')
		{
			if (original[++i] == '\0')
			{
				if (ft_strchr(&name[j], '/'))
					return (false);
				return (true);
			}
			while (original[i] == '*')
				++i;
			while (name[j] != original[i] && name[j] != '\0')
				++j;
		}
		else
		{
			if (name[j++] != original[i++])
				return (false);
		}
		if (name[j] == '\0' && original[i] == '/')
			return (3);
	}
	if (original[j] == '\0' && name[i] == '\0')
		return (true);
	return (false);
}

char	**paths_to_tab(t_path *paths)
{
	char	**str;

	while (paths != NULL)
	{
		add_string_char_2d(&str, paths->path);
	}
	return (str);
}

void	get_start_path(char *path, t_wildcard *wildcard)
{
	char	**tmp;
	char	*str;
	int		i;

	tmp = ft_split(path, '/');
	i = -1;
	while (tmp[++i])
	{
		if (ft_strchr(tmp[i], '*'))
		{
			if (tmp[i + 1] != NULL || (tmp[i + 1] == NULL && wildcard->dir == true))
				tmp[i++] = ft_strdup("/");
			tmp[i] = NULL;
			break ;
		}
	}
	if (wildcard->absolute == true)
		str = ft_strdup("/");
	wildcard->start_path = ft_re_strjoin(str, str_join_2d_and_free(tmp, '/'));
	if (wildcard->start_path == NULL)
		wildcard->start_path = ft_strdup("./");
}

char	*complete_path(char **path, int depth, bool absolute, bool dir)
{
	char	*str;
	int		i;

	i = 0;
	if (absolute == true)
		str = ft_strjoin("/", path[0]);
	else
		str = ft_strdup(path[0]);
	while (path[++i] != NULL)
	{
		str = ft_re_strjoin(str, '/');
		str = ft_re_strjoin(str, path[i]);
	}
	if (dir == true)
		str = ft_re_strjoin(str, '/');
	return (str);
}

char	*actual_path(char **path, int depth, bool absolute, bool dir)
{
	char	*str;
	int		i;

	i = -1;
	if (depth == 0 && absolute == true)
		return (ft_strdup("/"));
	else if (depth == 0)
		return (ft_strdup(path[0]));
	if (absolute == true)
	{
		str = ft_strjoin("/", path[0]);
		++i;
	}
	else
		str = ft_strdup(path[0]);
	while (++i < depth && path[i] != NULL)
	{
		str = ft_re_strjoin(str, '/');
		str = ft_re_strjoin(str, path[i]);
	}
	if (path[i] == NULL && dir == true)
		str = ft_re_strjoin(str, '/');
	return (str);
}
