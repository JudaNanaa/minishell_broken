/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:24:41 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/14 15:27:58 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"

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

/*
remplace les retours a la ligne (\n)
par "\n" ('\' + 'n')
*/
char	*replace_newline(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (count_char(str, '\n') == 0)
		return (str);
	res = ft_malloc(sizeof(char)
			* (ft_strlen(str) + count_char(str, '\n') + 1));
	if (res == NULL)
		handle_malloc_error("replace newline");
	while (str[++i] != '\0')
	{
		if (str[i] == '\n')
		{
			res[++j] = '\\';
			res[++j] = 'n';
		}
		else
			res[++j] = str[i];
	}
	res[++j] = '\0';
	return (res);
}
