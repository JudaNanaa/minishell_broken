/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:41:57 by madamou           #+#    #+#             */
/*   Updated: 2024/10/16 06:56:20 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

char *find_in_history(const char *text, int direction) {
    static const char *initial_text;
    static  char *save_text;
    static int index;
    HIST_ENTRY **history_list;
    int len;
    static char **good_tab;
    static int len_tab;
    char *cmd;
    int i;

    history_list =  history_get_history_state()->entries;
    if (!history_list)
        return NULL;
    
    if (initial_text == NULL || save_text == NULL || ft_strcmp(save_text, text) != 0) {
        i = 0;
		unlock(good_tab);
        good_tab = NULL;
        while (i < history_length)
        {
            cmd = history_list[i]->line;
            if (ft_strncmp(cmd, text, ft_strlen(text)) == 0)
                add_string_char_2d(&good_tab, cmd);
            i++;
        }
		lock(good_tab);
        len_tab = ft_strlen_2d(good_tab);
        initial_text = ft_strdup(text);
        index = len_tab;
    }
    len = ft_strlen(initial_text);
    while (index <= len_tab)
    {
        index += direction;
        if (index < 0)
        {
            index = 0;
            save_text = ft_strdup(text);
			lock(save_text);
            return ft_strdup(text);
        }
        else if (index == len_tab + 1 || index == len_tab)
        {
            index = len_tab;
            save_text = ft_strdup(initial_text);
			lock(save_text);
            return ft_strdup(initial_text);
        }
        cmd = good_tab[index];
        if (ft_strncmp(cmd, initial_text, len) == 0) {
            save_text = ft_strdup(cmd);
			lock(save_text);
            return ft_strdup(cmd);
        }
    }
    return NULL;
}

int arrow_handler(int count, int key) {
	char *match;
	const char *current;

	(void)count;
	if (key != 65 && key != 66)
    	return 1;	
	current = rl_line_buffer;
	if (key == 65)
        match = find_in_history(current, -1);
	else
		match = find_in_history(current, 1);
	if (match)
	{
		rl_replace_line(match, 1);
		rl_point = rl_end;
		free(match);
	}
    return 0;
}

