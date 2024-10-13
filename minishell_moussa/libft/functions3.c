/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:02:12 by madamou           #+#    #+#             */
/*   Updated: 2024/10/13 17:25:09 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fill_itoa(char *result, unsigned long long int nb, int size,
		char *base)
{
	if (nb >= (unsigned long long int)ft_strlen1(base))
	{
		ft_fill_itoa(result, nb / ft_strlen1(base), size - 1, base);
		ft_fill_itoa(result, nb % ft_strlen1(base), size, base);
	}
	if (nb < (unsigned long long int)ft_strlen1(base))
		result[size - 1] = base[nb];
}

char	*ft_itoa_long_long(unsigned long long int nb, char *base)
{
	int		size;
	char	*result;
	int		len_base;

	len_base = ft_strlen1(base);
	size = ft_size_malloc_long(nb, len_base);
	result = ft_malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	ft_fill_itoa(result, nb, size, base);
	result[size] = '\0';
	return (result);
}

char	*ft_pointer(char *print, void *ptr)
{
	unsigned long long int	true_ptr;
	char					*result;
	char					*base;

	base = "0123456789abcdef";
	true_ptr = (unsigned long long int)ptr;
	result = ft_itoa_long_long(true_ptr, base);
	if (!result)
		return (NULL);
	if (true_ptr != 0)
	{
		print = ft_reallocc(print, ft_strlen1(result) + 2);
		if (!print)
			return (ft_free(result), NULL);
		print = ft_strcatt(print, "0x");
		print = ft_strcatt(print, result);
	}
	else
	{
		print = ft_reallocc(print, 5);
		if (!print)
			return (ft_free(result), NULL);
		print = ft_strcatt(print, "(nil)");
	}
	return (ft_free(result), print);
}

char	*str_join_2d(char **str_2d, char *sep)
{
	char	*str;
	int		i;

	if (str_2d == NULL)
		return (NULL);
	str = NULL;
	i = -1;
	while (str_2d[++i] != NULL)
	{
		if (i != 0)
		{
			str = ft_re_strjoin(str, sep);
			if (str == NULL)
				return (NULL);
		}
		str = ft_re_strjoin(str, str_2d[i]);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	*str_join_2d_and_free(char **str_2d, char *sep)
{
	char	*str;

	if (str_2d == NULL)
		return (NULL);
	str = str_join_2d(str_2d, sep);
	ft_free_2d(str_2d);
	return (str);
}
