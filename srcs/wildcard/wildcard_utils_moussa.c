/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_moussa.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:24:58 by madamou           #+#    #+#             */
/*   Updated: 2024/12/16 15:19:44 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include <stdio.h>

int	ft_strncmp_reverse(char *s1, char *s2, int len_s2)
{
	int	len;

	len = ft_strlen(s1) - 1;
	len_s2--;
	while (len >= 0 && len_s2 >= 0)
	{
		if (s1[len] != s2[len_s2])
			return (s1[len] - s2[len_s2]);
		len--;
		len_s2--;
	}
	if (len == -1 && len_s2 != -1)
		return (-1);
	if (len_s2 == -1)
		return (0);
	return (s1[len] - s2[len_s2]);
}

void	add_back_wcards(t_wcards **wcards, t_wcards *new)
{
	t_wcards	*current;

	current = *wcards;
	if (!(*wcards))
	{
		*wcards = new;
		new->next = NULL;
		new->before = NULL;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
		new->before = current;
	}
}

void	create_node_wcards(t_wcards **wcards, char *str, int i, int j)
{
	t_wcards	*new;

	new = ft_malloc(sizeof(t_wcards));
	if (!new)
		handle_malloc_error("wildcards");
	new->content = ft_substr(str, i, j);
	new->content = expand_str(new->content);
	new->before = NULL;
	new->next = NULL;
	add_back_wcards(wcards, new);
}

void	skip_quote_wcards(char *str, int i, int *j)
{
	if (str[i + *j] == '"')
	{
		(*j)++;
		while (str[i + *j] != '"')
			(*j)++;
	}
	else if (str[i + *j] == '"')
	{
		(*j)++;
		while (str[i + *j] != '"')
			(*j)++;
	}
}