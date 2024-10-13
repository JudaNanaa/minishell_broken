/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/13 12:41:28 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_re_strdup(const char *src)
{
	char	*str;
	int		size;

	size = ft_strlen((char *)src) + 1;
	str = ft_malloc(sizeof(char) * size);
	if (!str)
		handle_malloc_error("ft_re_strdup");
	ft_strlcpy(str, src, size);
	ft_free((void *)src);
	return (str);
}
