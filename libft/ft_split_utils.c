/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:12:07 by madamou           #+#    #+#             */
/*   Updated: 2024/12/16 15:01:08 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_charset(char c, char *set)
{
	int	index;

	index = 0;
	while (set[index])
	{
		if (c == set[index])
			return (1);
		index++;
	}
	return (0);
}
