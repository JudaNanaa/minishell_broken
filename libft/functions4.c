/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 06:52:03 by madamou           #+#    #+#             */
/*   Updated: 2024/10/13 18:16:35 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			join2d(char **join, char **str1, char **str2);;

int	ft_size_malloc_long(unsigned long long int nb, int len_base)
{
	int	size;

	size = 1;
	while (nb / len_base > 0)
	{
		nb = nb / len_base;
		size++;
	}
	return (size);
}

char	**strdup2d(char **str)
{
	char	**res;
	int		i;

	res = ft_malloc(sizeof(char *) * (ft_strlen_2d(str) + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != NULL)
	{
		res[i] = ft_strdup(str[i]);
		if (res[i] == NULL)
			return (ft_free_2d(res), NULL);
	}
	res[i] = NULL;
	return (res);
}

char	**str2d_join(char **str1, char **str2)
{
	char	**join;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	if (str2 == NULL && str1 != NULL)
		return (str2 = strdup2d(str1), str2);
	if (str1 == NULL && str2 != NULL)
		return (str1 = strdup2d(str2), str1);
	join = ft_malloc(sizeof(char *)
			* (ft_strlen_2d(str1) + ft_strlen_2d(str2) + 1));
	if (join == NULL)
		return (NULL);
	if (join2d(join, str1, str2) == EXIT_FAILURE)
		return (NULL);
	return (join);
}

char	**re_str2djoin(char **str1, char **str2)
{
	char	**join;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str2 == NULL && str1 != NULL)
		return (str2 = strdup2d(str1), ft_free_2d(str1), str2);
	if (str1 == NULL && str2 != NULL)
		return (strdup2d(str2));
	join = ft_malloc(sizeof(char *)
			* (ft_strlen_2d(str1) + ft_strlen_2d(str2) + 1));
	if (join == NULL)
		return (ft_free_2d(str1), NULL);
	if (join2d(join, str1, str2) == EXIT_FAILURE)
		return (ft_free_2d(str1), NULL);
	return (ft_free_2d(str1), join);
}

static int	join2d(char **join, char **str1, char **str2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (str1[++i] != NULL)
	{
		join[++j] = ft_strdup(str1[i]);
		if (join[j] == NULL)
			return (ft_free_2d(join), EXIT_FAILURE);
	}
	i = -1;
	while (str2[++i] != NULL)
	{
		join[++j] = ft_strdup(str2[i]);
		if (join[j] == NULL)
			return (ft_free_2d(join), EXIT_FAILURE);
	}
	join[++j] = NULL;
	return (EXIT_SUCCESS);
}
