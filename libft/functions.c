/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:40 by madamou           #+#    #+#             */
/*   Updated: 2024/10/14 23:51:48 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_char(char *print, char c)
{
	int	i;

	i = ft_len_print(2);
	print = ft_reallocc(print, 3);
	if (!print)
		return (NULL);
	print[i] = c;
	ft_len_print(1);
	print[++i] = '\0';
	return (print);
}

char	*ft_decimal(char *print, int nb, int cas)
{
	char	*result;
	int		len_result;

	result = ft_itoa(nb);
	if (!result)
		return (ft_free(print), NULL);
	len_result = ft_strlen1(result);
	if ((cas == 2 || cas == 3) && nb >= 0)
		len_result++;
	print = ft_reallocc(print, len_result);
	if (!print)
		return (ft_free(print), NULL);
	if (cas == 2 && nb >= 0)
		print = ft_strcatt(print, " ");
	if (cas == 3 && nb >= 0)
		print = ft_strcatt(print, "+");
	print = ft_strcatt(print, result);
	return (ft_free(result), print);
}

char	*read_file(int fd)
{
	char	*temp;
	char	*str;

	temp = get_next_line(fd);
	if (temp == NULL)
		return (NULL);
	str = NULL;
	while (temp != NULL)
	{
		str = ft_re_strjoin(str, temp);
		ft_free(temp);
		if (str == NULL)
			return (NULL);
		temp = get_next_line(fd);
	}
	return (str);
}
