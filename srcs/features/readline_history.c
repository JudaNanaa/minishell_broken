/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:41:57 by madamou           #+#    #+#             */
/*   Updated: 2024/10/16 14:17:18 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

void	init_if_new_pattern(t_arrow *arrow, const char *text)
{
	int			i;
	char		*cmd;
	HIST_ENTRY	**history_list;

	i = 0;
	history_list = history_get_history_state()->entries;
	unlock(arrow->initial_text);
	arrow->initial_text = NULL;
	unlock(arrow->good_tab);
	arrow->good_tab = NULL;
	while (i < history_length)
	{
		cmd = history_list[i]->line;
		if (ft_strncmp(cmd, text, ft_strlen(text)) == 0)
			add_string_char_2d(&arrow->good_tab, cmd);
		i++;
	}
	lock(arrow->good_tab);
	arrow->len_tab = ft_strlen_2d(arrow->good_tab);
	arrow->initial_text = ft_strdup(text);
	lock(arrow->initial_text);
	arrow->index = arrow->len_tab;
}

char	*find_in_history(const char *text, int direction)
{
	static t_arrow	arrow;

	arrow.history_list = history_get_history_state()->entries;
	if (!arrow.history_list)
		return (NULL);
	if (arrow.initial_text == NULL || arrow.save_text == NULL
		|| ft_strcmp(arrow.save_text, text) != 0)
		init_if_new_pattern(&arrow, text);
	arrow.index += direction;
	if (arrow.index < 0)
	{
		arrow.index = 0;
		arrow.save_text = ft_strdup(text);
		return (lock(arrow.save_text), ft_strdup(text));
	}
	else if (arrow.index == arrow.len_tab + 1 || arrow.index == arrow.len_tab)
	{
		arrow.index = arrow.len_tab;
		arrow.save_text = ft_strdup(arrow.initial_text);
		return (lock(arrow.save_text), ft_strdup(arrow.initial_text));
	}
	arrow.save_text = ft_strdup(arrow.good_tab[arrow.index]);
	return (lock(arrow.save_text), ft_strdup(arrow.good_tab[arrow.index]));
}

int	arrow_handler(int count, int key)
{
	char		*match;
	const char	*current;

	(void)count;
	if (key != ARROW_UP && key != ARROW_DOWN)
		return (1);
	current = rl_line_buffer;
	if (key == ARROW_UP)
		match = find_in_history(current, UP);
	else
		match = find_in_history(current, DOWN);
	if (match)
	{
		rl_replace_line(match, 1);
		rl_point = rl_end;
		ft_free(match);
	}
	return (0);
}
