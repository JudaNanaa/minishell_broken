/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:14:46 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/09 00:26:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_char(char *str, char char_to_count)
{
	int	i;
	int	count;

	if (str == NULL)
		return (0);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == char_to_count)
			++count;
		i++;
	}
	return (count);
}
