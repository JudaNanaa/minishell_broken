/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:28:02 by ibaby             #+#    #+#             */
/*   Updated: 2024/12/16 15:09:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../includes/includes.h"
#include <time.h>
#include <unistd.h>

void	ctrl_D_mssg(int i, char *eof)
{
	t_data *data;

	data = get_data(NULL, GET);
	ft_fprintf(2, "%s: warning: here-document at line %i ", data->name, i);
	ft_fprintf(STDERR_FILENO, "delimited by end-of-file (wanted `%s')\n", eof);
}

int	get_herestr(t_file *new)
{
	if (new->path[0] == '\'' && new->path[ft_strlen(new->path) - 1] == '\'')
		new->expand_heredoc = false;
	else
	 	new->expand_heredoc = true;
	remove_quotes(new->path);
	add_string_char_2d(&new->heredoc_content, new->path);
	return (EXIT_SUCCESS);
}

int	get_heredoc(t_file *new)
{
	char	*input;
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL, GET);
	if (new->mode == HERESTRING)
		return (get_herestr(new));
	new->expand_heredoc = remove_quotes(new->path);
	while (++i)
	{
		if (isatty(STDIN_FILENO) == false)
			(ctrl_D_mssg(i, new->path), free_and_exit(data->status));
		input = readline("heredoc> ");
		if (g_signal != 0)
			return (set_status_if_signal(data), EXIT_FAILURE);
		if (input == NULL)
			return (ctrl_D_mssg(i, new->path), EXIT_SUCCESS);
		if (ft_strcmp(input, new->path) == 0)
			return (EXIT_SUCCESS);
		add_string_char_2d(&new->heredoc_content, input);
	}
	return (EXIT_SUCCESS);
}
