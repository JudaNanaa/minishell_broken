/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_moussa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:25:05 by madamou           #+#    #+#             */
/*   Updated: 2024/10/14 03:28:43 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void recursive_wcards(t_wildcard_moussa *node, char ***result);


int	is_match(char *name, t_wcards *wcards)
{
	if (ft_strcmp(wcards->content, "") != 0)
	{
		if (ft_strncmp(name, wcards->content, ft_strlen(wcards->content)) != 0)
			return (0);
	}
	name = name + ft_strlen(wcards->content);
	wcards = wcards->next;
	while (wcards->next)
	{
		if (ft_strcmp(wcards->content, "") != 0)
		{
			name = ft_strstr(name, wcards->content);
			if (!name)
				return (0);
		}
		wcards = wcards->next;
	}
	if (ft_strcmp(wcards->content, "") != 0)
	{
		if (ft_strncmp_reverse(name, wcards->content,
				ft_strlen(wcards->content)) != 0)
			return (0);
	}
	return (1);
}

char *find_base_path(char *str)
{
	int i;
	char *dest;
	char *chr;

	dest = ft_strdup(str);
	chr = ft_strchr(dest, '*');
	chr[0] = '\0';
	i = ft_strlen(dest);
	while (i >= 0 && str[i] != '/')
	{
		dest[i] = '\0';
		i--;
	}
	if (i == -1)
	{
		dest = ft_strdup("");
		return (dest);
	}
	return (dest);
}

t_wildcard_moussa *new_node_wildcard(void)
{
	t_wildcard_moussa *new;

	new = ft_malloc(sizeof(t_wildcard_moussa));
	if (new == NULL)
		handle_malloc_error("wildcards");
	return (new);
}

t_wcards	*init_wcards(char *str)
{
	t_wcards	*wcards;
	int			i;
	int			j;

	i = 0;
	j = 0;
	wcards = NULL;
	while (str[i + j])
	{
		skip_quote_wcards(str, i, &j);
		if (str[i + j] == '*')
		{
			create_node_wcards(&wcards, str, i, j);
			i += j + 1;
			j = -1;
		}
		j++;
	}
	create_node_wcards(&wcards, str, i, j);
	return (wcards);
}

void add_back_wildcard(t_wildcard_moussa **first, t_wildcard_moussa *to_add)
{
	t_wildcard_moussa *buff;

	if (*first == NULL)
		*first = to_add;
	else
	{
		buff = *first;
		while (buff->next)
			buff = buff->next;
		buff->next = to_add;
	}
	to_add->next = NULL;
}

DIR *ft_opendir(char *path)
{
	DIR *dir;

	if (path[0] == '\0')
		dir = opendir(".");
	else
		dir = opendir(path);
	return (dir);
}

int check_name(char *name, char **expand)
{
	if (expand[0][0] == '.' && name[0] == '.' && expand[1] == NULL)
		return (true);
	if ((ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
		&& expand[1] == NULL)
		return (false);
	if (expand[0][0] != '.' && name[0] == '.')
		return (false);
	return (true);
}

void recall_recursive_wcards(t_wildcard_moussa *node, struct dirent *elem,
	char ***result, int flag)
{
	t_wildcard_moussa new;

	new.base_path = ft_strjoin(node->base_path, elem->d_name);
	if (flag == 1)
		new.base_path = ft_re_strjoin(new.base_path, "/");
	new.to_expand = strdup2d(&node->to_expand[1]);
	new.dir = node->dir;
	recursive_wcards(&new, result);	
}

void recursive_wcards(t_wildcard_moussa *node, char ***result)
{
	DIR *dir;
	struct dirent *elem;
	t_wcards *wcards;

	if (!node->to_expand[0])
	{
		add_string_char_2d(result, node->base_path);
		return;
	}
	wcards = init_wcards(node->to_expand[0]);
	dir = ft_opendir(node->base_path);
	if (dir == NULL)
		return ;
	elem = readdir(dir);
	while (elem != NULL)
	{
		if (is_match(elem->d_name, wcards) && check_name(elem->d_name, node->to_expand))
		{
			if (node->to_expand[1] != NULL && elem->d_type == DT_DIR)
				recall_recursive_wcards(node, elem, result, 1);
			else if (node->to_expand[1] == NULL)
			{
				if (node->dir == true && elem->d_type == DT_DIR)
					recall_recursive_wcards(node, elem, result, 1);
				else if (node->dir == false)
					recall_recursive_wcards(node, elem, result, 0);
			}
		}
		elem = readdir(dir);
	}
	closedir(dir);
}



int	ft_strcmp_nascii(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*true_s1;
	unsigned char	*true_s2;

	true_s1 = (unsigned char *)s1;
	true_s2 = (unsigned char *)s2;
	i = 0;
	while (true_s2[i] || true_s1[i])
	{
		if (ft_tolower(true_s1[i]) != ft_tolower(true_s2[i]))
		{
			if (ft_tolower(true_s1[i]) < ft_tolower(true_s2[i]))
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

void sort_str2d_nascii(char **str)
{
	int		temp;
	char	*lower;
	int		i;
	int		y;

	y = -1;
	while (str[++y] != NULL)
	{
		i = y;
		temp = i;
		lower = str[i];
		while (str[++i] != NULL)
		{
			if (ft_strcmp_nascii(lower, str[i]) > 0)
			{
				temp = i;
				lower = str[i];
			}
		}
		str[temp] = str[y];
		str[y] = lower;
	}	
}

char **expand_wildcards(char *to_expand)
{
	t_wildcard_moussa *node;
	char **result;
	char *str;

	result = NULL;
	node = new_node_wildcard();
	node->base_path = find_base_path(to_expand);
	if (to_expand[ft_strlen(to_expand) - 1] == '/')
		node->dir = true;
	else
		node->dir = false;
	if (node->base_path[0])
	{
		str = ft_strstr(to_expand, node->base_path) + ft_strlen(node->base_path);
		node->to_expand = ft_split(str, "/");
	}
	else
		node->to_expand = ft_split(to_expand, "/");
	recursive_wcards(node, &result);
	if (result == NULL)
		add_string_char_2d(&result, to_expand);
	sort_str2d_nascii(result);
	return (result);
}
