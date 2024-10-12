/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:26:16 by madamou           #+#    #+#             */
/*   Updated: 2024/10/12 19:21:40 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "parsing.h"
#include <readline/chardefs.h>
#include <unistd.h>

char	*quote_or_dquote(char *str, char *prompt, t_data *data, char *flag)
{
	char	*new_line;

	new_line = readline(prompt);
	if (!new_line)
	{
		if (ft_strcmp(flag, NEWLINE1) == 0)
		{
		if (ft_strcmp(prompt, "quote> ") == 0)
			ft_putendl_fd(S_U_EOF, 2);
		else
			ft_putendl_fd(D_U_EOF, 2);
		}
		ft_fprintf(STDERR_FILENO,
			"%s: syntax error: unexpected end of file\n", data->name);
		if (ft_strcmp(flag, SEMICOLON) == 0 || ft_strcmp(flag, SPACE1) == 0)
			(ft_fprintf(2, "exit\n"), free_and_exit(data->status));
		return (data->status = 2, NULL);
	}
	str = ft_re_strjoin(str, flag);
	str = ft_re_strjoin(str, new_line);
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
		str = quote_or_dquote(str, "dquote> ", data, NEWLINE1);
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
		str = quote_or_dquote(str, "quote> ", data, NEWLINE1);
		*i = -1;
	}
	return (str);
}

char	*check_last_token(char *str, int *i, t_data *data)
{
	char **split;
	int len;

	split = ft_split(str, " \t");
	len  = ft_strlen_2d(split);
	if (ft_strcmp(split[len - 1], "|") == 0 && ft_strcmp(split[0], "|") != 0)
	{
		str = quote_or_dquote(str, "pipe> ", data, SPACE1);
		*i = 0;
	}
	if (ft_strcmp(split[len - 1], "||") == 0 && ft_strcmp(split[0], "||") != 0)
	{
		str = quote_or_dquote(str, "or> ", data, SPACE1);
		*i = 0;
	}
	if (ft_strcmp(split[len - 1], "&&") == 0 && ft_strcmp(split[0], "&&") != 0)
	{
		str = quote_or_dquote(str, "and> ", data, SPACE1);
		*i = 0;
	}
	return (str);
}

char	*check_if_paranthesis_close(char *str, int i, t_data *data)
{
	int	open_parenthesis;
	int	close_parenthesis;

	open_parenthesis = 0;
	close_parenthesis = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			continue_until_find(0, &i, str, '"');
		if (str[i] == '\'')
			continue_until_find(0, &i, str, '\'');
		if (str[i] == '(')
			open_parenthesis++;
		if (str[i] == ')')
			close_parenthesis++;
	}
	if (open_parenthesis < close_parenthesis)
		return (NULL);
	if (open_parenthesis == close_parenthesis)
		return (str);
	str = quote_or_dquote(str, "subshell> ", data, SEMICOLON);
	return (check_if_paranthesis_close(str, -1, data));
}

char	*check_if_command_line_is_good(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (i == 0)
	{
		while (g_signal == 0 && str[i])
		{
			if (g_signal == 0 && str[i] == '"')
				str = check_if_dquote_close(str, &i, data);
			else if (g_signal == 0 && str[i] == '\'')
				str = check_if_quote_close(str, &i, data);
			i++;
		}
		if (!str[i])
			str = check_last_token(str, &i, data);
	}
	if (g_signal != 0)
		return (set_status_if_signal(data), NULL);
	return (check_if_paranthesis_close(str, -1, data));
}
