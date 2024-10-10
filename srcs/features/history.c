/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:23:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/18 16:43:19 by ibaby            ###   ########.fr       */
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
	if (ft_putendl_fd(str, fd) == -1)
		return ((void)close(fd));
	ft_close_fd(&fd);
}

void	init_history(void)
{
	int		fd;
	char	*str;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return (error_log("init_history: open(history_file)", true),
			ft_close_fd(&fd));
	str = get_next_line(fd);
	if (str == NULL)
		return (ft_close_fd(&fd));
	str = ft_strtrim(str, "\n");
	add_and_save(str);
	while (str != NULL && str[0] != '\0')
	{
		ft_free(str);
		str = get_next_line(fd);
		if (str == NULL)
			return (ft_close_fd(&fd));
		str = ft_strtrim(str, "\n");
		if (str == NULL)
			return (ft_close_fd(&fd));
		add_and_save(str);
	}
	ft_close_fd(&fd);
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
