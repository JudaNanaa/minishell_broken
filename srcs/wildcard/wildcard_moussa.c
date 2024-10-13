/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_moussa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:25:05 by madamou           #+#    #+#             */
/*   Updated: 2024/10/13 17:17:38 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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
		ft_strcpy(dest, ".");
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

void check_dir(t_wildcard_moussa *node, char ***result)
{
	DIR *dir;
	struct dirent *elem;
	t_wildcard_moussa *child_node;
	t_wildcard_moussa *new;
	t_wcards *wcards;

	if (!node->to_expand[0])
	{
		add_string_char_2d(result, node->base_path);
		return;
	}
	wcards = init_wcards(node->to_expand[0]);
	child_node = NULL;
	dir = opendir(node->base_path);
	if (dir == NULL)
		return ;
	elem = readdir(dir);
	while (elem != NULL)
	{
		if (elem->d_name[0] != '.'  && is_match(elem->d_name, wcards))
		{
			if (node->to_expand[1] != NULL && elem->d_type == DT_DIR)
			{
				new = new_node_wildcard();
				new->base_path = ft_strjoin(node->base_path, elem->d_name);
				new->base_path = ft_strjoin(new->base_path, "/");
				new->to_expand = strdup2d(&node->to_expand[1]);
				new->dir = node->dir;
				printf("%s\n", new->base_path);
				check_dir(new, result);
			}
			else if (node->to_expand[1] == NULL)
			{
				if (node->dir == true && elem->d_type != DT_DIR)
					return ;
				if (node->dir == true && elem->d_type == DT_DIR)
				{
					new = new_node_wildcard();
					new->base_path = ft_strjoin(node->base_path, elem->d_name);
					new->base_path = ft_strjoin(new->base_path, "/");
					new->to_expand = strdup2d(&node->to_expand[1]);
					new->dir = node->dir;
					printf("%s\n", new->base_path);
					check_dir(new, result);				
				}
				else
				{
					new = new_node_wildcard();
					new->base_path = ft_strjoin(node->base_path, elem->d_name);
					new->to_expand = strdup2d(&node->to_expand[1]);
					new->dir = node->dir;
					printf("%s\n", new->base_path);
					check_dir(new, result);				
				}
			}
			// add_back_wildcard(&child_node, new);
		}
		elem = readdir(dir);
	}
	closedir(dir);
}

void expand_wildcards(char *to_expand)
{
	t_wildcard_moussa *node;
	char **result;

	result = NULL;
	node = new_node_wildcard();
	node->base_path =  find_base_path(to_expand);
	printf("base path == %s\n",node->base_path);
	if (to_expand[ft_strlen(to_expand) - 1] == '/')
		node->dir = true;
	else
		node->dir = false;
	node->to_expand = ft_split(ft_strstr(to_expand, node->base_path) + ft_strlen(node->base_path), "/");
	printf("node->to_expand :\n");
	printf_2d_array(node->to_expand);
	printf("-------------------------------------------------------------------\n");
	check_dir(node, &result);
	printf("-------------------------------------------------------------------\n");
	printf("result :\n");
	printf_2d_array(result);
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
	expand_wildcards(argv[1]);
}