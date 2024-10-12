/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:16:53 by madamou           #+#    #+#             */
/*   Updated: 2024/10/12 16:09:11 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include <string.h>

void	error_pwd(char *buffer, t_data *info)
{
	ft_free(buffer);
	if (errno == ENOENT)
	{
		ft_fprintf(2, "pwd: error retrieving current directory: ");
		ft_fprintf(2, "getcwd: cannot access parent directories: ");
	}
	perror("pwd");
	info->status = 1;
}

char	*ft_pwd(int cas, t_data *info)
{
	char	*buffer;
	size_t	size;
	char	*check;

	size = 1000;
	check = NULL;
	while (!check)
	{
		size *= 2;
		buffer = ft_malloc(sizeof(char) * size);
		if (!buffer)
			handle_malloc_error("pwd");
		ft_memset(buffer, 0, size);
		check = getcwd(buffer, size);
		if (!check && errno == ERANGE)
			ft_free(buffer);
		else if (!check && errno != ERANGE)
		{
			error_pwd(buffer, info);
			return (NULL);
		}
	}
	if (cas == PRINT)
		(ft_printf("%s\n", buffer), ft_free(buffer));
	else if (cas == GET)
		return (buffer);
	return (info->status = 0, buffer);
}
