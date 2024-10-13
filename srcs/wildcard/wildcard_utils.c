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

t_path	*file_path(struct dirent *file, t_wildcard *wildcard)
{
	t_path	*node;
	char	*path;

	// if (wildcard->absolute == false && ft_strchr(wildcard->complete_path, '/') == 0)
	// 	path = ft_strdup(wildcard->start_path + 2);
	// printf("\nBefore: \n[%s/%s]\n\n", wildcard->start_path, file->d_name);
	if (wildcard->absolute == false && ft_strcmp(wildcard->start_path, ".") == 0)
		path = NULL;
	else if (wildcard->absolute == false)
		path = ft_strdup(wildcard->start_path);
	else
		path = ft_strdup(wildcard->start_path);

	if (path != NULL && ft_strcmp(wildcard->start_path, "/") != 0)
		path = ft_re_strjoin(path, "/");
	path = ft_re_strjoin(path, file->d_name);
	if (wildcard->dir == true)
		path = ft_re_strjoin(path, "/");
	// printf("\n\nDEBUUUUUUUUUUUUUUUUUUUG: \n[%s]\n\n", path);
	node = ft_malloc(sizeof(t_path));
	node->next = NULL;
	if (wildcard->absolute == false && ft_strncmp(path, "./", 2) == 0)
		path += 2;
	node->path = path;
	// printf("BEFORE: %s\n", path);
	return (node);
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

bool	is_final_file(struct dirent *file, t_wildcard *wildcard)
{
	printf("file: %s\n", file->d_name);
	if (is_valid_file(file, wildcard) == true)
		return (true);
	else
		return (false);
}

int	is_valid_file(struct dirent *file, t_wildcard *wildcard)
{
	char	*actual_tmp;

	if (wildcard->dir == true && file->d_type != DT_DIR)
		return (false);
	if (is_hidden(file->d_name, wildcard) == false)
		return (false);
	// if (wildcard->start_path[ft_strlen(wildcard->start_path) - 1] != '/')
	if (ft_strcmp(wildcard->start_path, "/") == 0)
		actual_tmp = ft_strdup(wildcard->start_path);
	else
		actual_tmp = ft_strjoin(wildcard->start_path, "/");
	actual_tmp = ft_re_strjoin(actual_tmp, file->d_name);
	return (is_valid_name(actual_tmp, wildcard->complete_path));
}

int	is_valid_name(char *name, char *original)
{
	int	i;
	int	j;

	j = 0;
	i = 0;

	if (ft_strcmp(name, "./") == 0)
		name = ft_strdup(name + 2);
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
	if ((original[i] == '\0' || (original[i] == '*' && original[i + 1] == '\0'))
		&& name[j] == '\0')
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

	tmp = ft_split(path, "/");
	str = NULL;
	// if (ft_strcmp(tmp[0], ".") == 0)
	// 	tmp[0] = ft_re_strjoin(tmp[0], "/");
	i = -1;
	while (tmp[++i])
	{
		if (ft_strchr(tmp[i], '*'))
		{
			// if (tmp[i + 1] != NULL || (tmp[i + 1] == NULL && wildcard->dir == true))
			// 	tmp[i++] = ft_strdup("/");
			tmp[i] = NULL;
			break ;
		}
	}
	if (wildcard->absolute == true)
		str = ft_strdup("/");
	wildcard->start_path = ft_re_strjoin(str, str_join_2d_and_free(tmp, "/"));
	if (wildcard->start_path == NULL)
		wildcard->start_path = ft_strdup("./");
}

// char	*complete_path(char **path, int depth, bool absolute, bool dir)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	if (absolute == true)
// 		str = ft_strjoin("/", path[0]);
// 	else
// 		str = ft_strdup(path[0]);
// 	while (path[++i] != NULL)
// 	{
// 		str = ft_re_strjoin(str, "/");
// 		str = ft_re_strjoin(str, path[i]);
// 	}
// 	if (dir == true)
// 		str = ft_re_strjoin(str, "/");
// 	return (str);
// }

// char	*actual_path(char **path, int depth, bool absolute, bool dir)
// {
// 	char	*str;
// 	int		i;

// 	i = -1;
// 	if (depth == 0 && absolute == true)
// 		return (ft_strdup("/"));
// 	else if (depth == 0)
// 		return (ft_strdup(path[0]));
// 	if (absolute == true)
// 	{
// 		str = ft_strjoin("/", path[0]);
// 		++i;
// 	}
// 	else
// 		str = ft_strdup(path[0]);
// 	while (++i < depth && path[i] != NULL)
// 	{
// 		str = ft_re_strjoin(str, '/');
// 		str = ft_re_strjoin(str, path[i]);
// 	}
// 	if (path[i] == NULL && dir == true)
// 		str = ft_re_strjoin(str, '/');
// 	return (str);
// }