/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:26:16 by madamou           #+#    #+#             */
/*   Updated: 2024/10/09 01:18:25 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

char	*quote_or_dquote(char *str, char *prompt, t_data *data)
{
	char	*new_line;

	new_line = readline(prompt);
	if (!new_line)
	{
		if (ft_strcmp(prompt, "quote> ") == 0)
			ft_putendl_fd(S_U_EOF, 2);
		else
			ft_putendl_fd(D_U_EOF, 2);
		ft_putendl_fd("minshell: syntax error: unexpected end of file", 2);
		return (data->status = 2, NULL);
	}
	str = ft_realloc(str, ft_strlen(new_line) + 1);
	if (!str)
		handle_malloc_error(prompt);
	ft_strcat(str, "\n");
	ft_strcat(str, new_line);
	free(new_line);
	return (str);
}

char	*check_if_dquote_close(char *str, int *i, t_data *data)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] == '\0')
	{
		str = quote_or_dquote(str, "dquote> ", data);
		*i = -1;
	}
	return (str);
}

char	*check_if_quote_close(char *str, int *i, t_data *data)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\0')
	{
		str = quote_or_dquote(str, "quote> ", data);
		*i = -1;
	}
	return (str);
}

int	check_if_paranthesis_close(char *str, int i)
{
	int	open_parenthesis;
	int	close_parenthesis;

	open_parenthesis = 0;
	close_parenthesis = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '(')
			open_parenthesis++;
		if (str[i] == ')')
			close_parenthesis++;
	}
	return (open_parenthesis - close_parenthesis);
}

char	*check_if_command_line_is_good(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (g_signal == 0 && str && str[i])
	{
		if (g_signal == 0 && str && str[i] == '"')
			str = check_if_dquote_close(str, &i, data);
		else if (g_signal == 0 && str && str[i] == '\'')
			str = check_if_quote_close(str, &i, data);
		i++;
	}
	if (!str)
		return (NULL);
	if (g_signal != 0)
		return (set_status_if_signal(data), NULL);
	check_if_paranthesis_close(str, -1); // voir si on gere les parentheses pas fermee
	return (str);
}
