/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 01:38:28 by madamou           #+#    #+#             */
/*   Updated: 2024/10/17 00:10:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	is_a_separator(char *c)
{
	if (*c == '>'  || *c == '<' || *c == '|' || ft_strncmp(c, "&&", 2) == 0|| *c == ';' || *c == '\n')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	continue_until_find(int i, int *j, char *str, char to_find)
{
	++(*j);
	while (str[i + *j] != to_find)
		(*j)++;
}

int	is_a_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}