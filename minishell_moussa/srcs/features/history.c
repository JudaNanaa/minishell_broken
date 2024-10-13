/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:23:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/13 12:00:34 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

void	ft_addhistory(char	*str)
{
	int	fd;

	if (str == NULL)
		return ;
	if (get_last_history(NULL, false) != NULL
		&& ft_strcmp(str, get_last_history(NULL, false)) == 0)
		return ;
	add_and_save(str);
	fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (error_log("add_history: open(history_file)", true),
			(void)close(fd));
	ft_putendl_fd(str, fd);
	close(fd);
}

void	init_history(void)
{
	int		fd;
	char	*str;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	str = get_next_line(fd);
	if (str == NULL)
		return ((void)close(fd));
	str = ft_strtrim(str, "\n");
	add_and_save(str);
	while (str != NULL)
	{
		ft_free(str);
		str = get_next_line(fd);
		if (str == NULL)
			return ((void)close(fd));
		str = ft_strtrim(str, "\n");
		if (str == NULL)
			return ((void)close(fd));
		add_and_save(str);
	}
	close(fd);
}

void	add_and_save(char *str)
{
	char	*save;

	if (str == NULL || *str == '\0')
		return ;
	save = get_last_history(NULL, false);
	if (save != NULL && ft_strcmp(str, save) == 0)
		return ;
	add_history(str);
	get_last_history(str, true);
}

char	*get_last_history(char *str, bool set)
{
	static char	*save = NULL;

	if (set == true)
		return (save = ft_strdup(str), lock(save), NULL);
	return (save);
}
