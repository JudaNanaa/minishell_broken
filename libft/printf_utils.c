/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:59:58 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 05:29:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcatt(char *print, char *src)
{
	size_t	i;
	size_t	j;

	i = ft_len_print(2);
	j = 0;
	while (src[j])
	{
		print[i++] = src[j++];
		ft_len_print(1);
	}
	print[i] = '\0';
	return (print);
}

void	ft_putstrr(char *s)
{
	if (s)
	{
		write(1, s, ft_len_print(2));
		ft_free(s);
	}
}

int	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strcpyy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (i < ft_len_print(2))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_reallocc(char *print, int len_realloc)
{
	char	*tmp;
	int		i;

	i = ft_len_print(2);
	tmp = ft_malloc(sizeof(char) * (i + len_realloc + 1));
	if (!tmp)
		return (ft_free(print), NULL);
	tmp[0] = '\0';
	tmp = ft_strcpyy(tmp, print);
	ft_free(print);
	return (tmp);
}
