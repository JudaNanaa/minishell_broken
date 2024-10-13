/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:20 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/13 12:42:25 by ibaby            ###   ########.fr       */
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
		handle_malloc_error("ft_re_strjoin: ft_re_strdup");
	ft_strlcpy(str, src, size);
	ft_free((void *)src);
	return (str);
}

char	*ft_re_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;

	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_re_strdup(s1));
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		handle_malloc_error("ft_re_strjoin");
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len + 1);
	ft_free((void *)s1);
	return (str);
}
