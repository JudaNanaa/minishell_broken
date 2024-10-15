/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:19:32 by madamou           #+#    #+#             */
/*   Updated: 2024/10/15 10:46:18 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "builtins.h"
#include <time.h>

void	print_alias(t_alias *alias)
{
	// while (alias)
	// {
	// 	printf("alias %s", alias->key);
	// 	if (alias->value)
	// 		printf("=\"%s\"\n", alias->value);
	// 	else
	// 		printf("\n");
	// 	alias = alias->next;
	// }
	while (alias)
	{
		printf("%s='%s'\n", alias->key, alias->value);
		alias = alias->next;
	}
}

t_alias *init_alias(char *alias)
{
	t_alias	*new;
	char	**split;

	new = ft_malloc(sizeof(t_alias));
	if (!new)
		handle_malloc_error("init alias");
	split = split_first_value(alias, '=');
	if (!split)
		return (ft_free(new), NULL);
	new->key = split[0];
	new->value = split[1];
	ft_free(split);
	new->next = NULL;
	new->prev = NULL;
	lock(new);
	lock(new->key);
	lock(new->value);
	return (new);
}

char	*ft_getalias(char *key)
{
	t_data	*data;
	t_alias	*tmp;

	data = get_data(NULL, GET);
	tmp = data->alias;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

t_alias	*search_in_alias(char *key)
{
	t_data	*data;
	t_alias	*tmp;

	data = get_data(NULL, GET);
	tmp = data->alias;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void add_back_alias(t_alias **alias, t_alias *to_add)
{
	t_alias *buff;

	if (*alias == NULL)
	{
		*alias = to_add;
		to_add->prev = NULL;
	}
	else if (search_in_alias(to_add->key))
	{
		buff = search_in_alias(to_add->key);
		ft_free(buff->value);
		buff->value = to_add->value;
		ft_free(to_add->key);
		ft_free(to_add);
	}
	else
	{
		buff = *alias;
		while (buff->next)
			buff = buff->next;
		buff->next = to_add;
		to_add->prev = buff;
	}
	to_add->next = NULL;
}

int	add_in_list_alias(t_data *data, char *content)
{
	char	**key;
	t_alias	*current;
	t_alias	*to_add;

	key = split_first_value(content, '=');
	current = search_in_alias(key[0]);
	if (current)
	{
		if (key[1])
		{
			ft_free(current->value);
			current->value = ft_strdup(key[1]);
			lock(current->value);
		}
	}
	else
	{
		to_add = init_alias(content);
		if (!to_add)
			return (-1);
		add_back_alias(&data->alias, to_add);
	}
	(ft_free(key[0]), ft_free(key[1]), ft_free(key));
	return (1);
}

int	ft_alias(t_data *data, char **content)
{
	int	i;

	i = 1;
	data->status = 0;
	while (content[i])
	{
		if (is_a_good_variable(content[i]))
		{
			if (add_in_list_alias(data, content[i]) == -1)
				handle_malloc_error("export");
		}
		else
		{
			printf("%s: alias: `%s': : not found\n", data->name,
				content[i]);
			data->status = 1;
		}
		i++;
	}
	if (i == 1)
		print_alias(data->alias);
	return (data->status);
}