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
	str[i] = '\0';
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
	get_start_path(path, &wildcard);
	// printf("start path: %s\n", wildcard.start_path);
	wildcard.complete_path = path;
	// printf("complete path: %s\n", wildcard.complete_path);
	return (replace_wildcard(&wildcard));
}

char	**path_to_tab(t_path *paths)
{
	char	**str;

	str = NULL;
	while (paths != NULL)
	{
		add_string_char_2d(&str, paths->path);
		paths = paths->next;
	}
	return (str);
}

int	expand_wildcard(t_token *cmd)
{
	int			i;
	char		**new_args;

	if (cmd->args == NULL)
		return (EXIT_SUCCESS);
	i = -1;
	new_args = NULL;
	while (cmd->args[++i] != NULL)
	{
		if (have_to_expand_wildcards(cmd->args[i]) == true)
			new_args = re_str2djoin(new_args, path_to_tab(search_paths(cmd->args[i])));
		else
			add_string_char_2d(&new_args, cmd->args[i]);
	}
	cmd->args = new_args;
	return (EXIT_SUCCESS);
}

bool	check_path(char *path, t_wildcard *wildcard)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (wildcard->complete_path[i] != '\0' && path[j] != '\0')
	{
		if (wildcard->complete_path[i] == '*')
		{
			if (wildcard->complete_path[++i] == '\0')
			{
				if (ft_strchr(&path[j], '/'))
					return (false);
				return (true);
			}
			while (wildcard->complete_path[i] == '*')
				++i;
			while (path[j] != wildcard->complete_path[i] && path[j] != '\0')
				++j;
		}
		else
		{
			if (path[j++] != wildcard->complete_path[i++])
				return (false);
		}
	}
	if (wildcard->complete_path[i] == '\0' && path[j] == '\0')
		return (true);
	return (false);
}

t_path	*next_depth(struct dirent *file, t_wildcard *wildcard)
{
	char	*path;
	char	**tmp;

	tmp = ft_split(wildcard->complete_path, "/");
	// if (ft_strncmp())
	tmp[count_char(wildcard->start_path, '/') + 1] = ft_strdup(file->d_name);
	if (wildcard->absolute == false && ft_strcmp(tmp[0], ".") == 0)
		tmp = &tmp[1];
	path = str_join_2d_and_free(tmp, "/");
	if (wildcard->dir == true)
		path = ft_re_strjoin(path, "/");
	// printf("WSH %s ! WSH %s\n", path, wildcard->complete_path);
	if (check_path(path, wildcard) == true && access(path, F_OK) == 0)
		return (file_path(file, wildcard));
	return (search_paths(path));
}

void	add_path(t_path *paths, t_path **list)
{
	t_path	*curr;

	if (paths == NULL)
		return ;
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
	// if (is_final_file(wildcard))
		// return ()
	dir = opendir(wildcard->start_path);
	if (dir == NULL)
		return (NULL);
	file = readdir(dir);
	while (file != NULL)
	{
		tmp = is_valid_file(file, wildcard);
		// printf("file: %s, %i\n", file->d_name, tmp);
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
	return (list);
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("mets deux arguments\n");
		return 1;
	}
	if (ft_strchr(argv[1], '*') == NULL)
	{
		printf("ya pas de wildcard\n");
		return 1;
	}
	char **str = path_to_tab(search_paths(argv[1]));
	printf("\nfinal:\n");
	sort_str2d(str);
	printf_2d_array(str);
}
