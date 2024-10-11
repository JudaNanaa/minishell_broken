/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:28:02 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/11 23:55:01 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../includes/includes.h"

void	ctrl_D_mssg(int i, char *eof)
{
	ft_fprintf(STDERR_FILENO, "bash: warning: here-document at line %i ", i);
	ft_fprintf(STDERR_FILENO, "delimited by end-of-file (wanted `%s')\n", eof);
}

int	get_heredoc(t_file *new)
{
	char	*input;
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL, GET);
	while (++i)
	{
		input = readline("heredoc> ");
		if (input == NULL)
			return (ctrl_D_mssg(i, new->path), EXIT_SUCCESS);
		if (g_signal != 0)
			return (set_status_if_signal(data), EXIT_FAILURE);
		if (ft_strcmp(input, new->path) == 0)
			return (EXIT_SUCCESS);
		add_string_char_2d(&new->heredoc_content, input);
	}
	return (EXIT_SUCCESS);
}

char	*ft_normal_format(char *line, char *dest, int *i)
{
	int	len;

	len = ft_strlen(dest);
	dest = ft_realloc(dest, sizeof(char) * 2);
	if (!dest)
		return (NULL);
	while (line[*i] && line[*i] != '$')
	{
		dest = ft_realloc(dest, sizeof(char) * 2);
		if (!dest)
			return (NULL);
		dest[len++] = line[*i];
		dest[len] = '\0';
		(*i)++;
	}
	return (dest);
}

char	*ft_create_variable(char *line, int *i)
{
	int		j;
	char	*var;

	j = 0;
	if (line[*i] == '?')
		j = 1;
	else if (line[*i] == '{')
	{
		(*i)++;
		while (line[*i + j] != '}')
			j++;
	}
	else
	{
		while (line[*i + j] && is_a_var_char(line[*i + j]))
			j++;
	}
	var = ft_malloc(sizeof(char) * (j + 2));
	if (!var)
		return (NULL);
	var = ft_strncpy(var, &line[*i], j);
	if (line[*i + j] == '}')
		(*i)++;
	*i += j;
	return (var[j++] = '=', var[j] = '\0', var);
}

char	*ft_check_if_variable_exist(char **envp, char *var, char *dest, int j)
{
	int		index;
	t_data	*data;

	data = get_data(NULL, GET);
	index = 0;
	if (ft_strcmp(var, "?=") == 0)
		return (ft_free(var), ft_sprintf("%s%d", dest, data->status));
	else if (var[0] == '=')
		return (ft_free(var), ft_sprintf("%s$", dest, data->status));
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], j) == 0)
			return (ft_free(var), ft_re_strjoin(dest, &envp[index][j]));
		index++;
	}
	return (ft_free(var), dest);
}

char	*ft_is_env_variable(char *line, char **envp)
{
	char	*dest;
	char	*var;
	int		i;

	i = 0;
	dest = NULL;
	while (line[i])
	{
		dest = ft_normal_format(line, dest, &i);
		if (dest == NULL)
			return (NULL);
		if (!line[i])
			return (dest);
		if (line[i] == '$')
			i++;
		var = ft_create_variable(line, &i);
		if (!var)
			return (ft_free(dest), NULL);
		dest = ft_check_if_variable_exist(envp, var, dest, ft_strlen(var));
		if (!dest)
			return (NULL);
	}
	return (dest);
}

char	*expand_line(char *line)
{
	char	*dest;
	char	**envp;
	t_data	*data;

	data = get_data(NULL, GET);
	dest = ft_strchr(line, '$');
	if (!dest)
		return (line);
	envp = t_env_to_envp(data->env, ALL);
	if (!envp)
		handle_malloc_error("heredoc");
	dest = ft_is_env_variable(line, envp);
	ft_free_2d(envp);
	if (!dest)
		handle_malloc_error("heredoc");
	return (ft_free(line), dest);
}

char	*normal_or_dollar(char *str, int *i, int j)
{
	char	*sub_str;
	char	*end_str;

	sub_str = ft_substr(str, *i, j);
	if (!sub_str)
		handle_malloc_error("expand variable");
	sub_str = expand_line(sub_str);
	end_str = ft_substr(str, *i + j, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str) + 1);
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}




char	*if_dquote(char *str, int *i)
{
	int		j;
	char	*sub_str;
	char	*end_str;

	j = 1;
	while (str[*i + j] != '"')
		j++;
	sub_str = ft_substr(str, *i + 1, j - 1);
	if (!sub_str)
		handle_malloc_error("expand variable");
	sub_str = expand_line(sub_str);
	end_str = ft_substr(str, *i + j + 1, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str));
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}

char	*if_cursh(char *str, int *i)
{
	int		j;
	char	*sub_str;
	char	*end_str;

	j = 0;
	while (str[*i + j] != '}')
		j++;
	sub_str = ft_substr(str, *i, j + 1);
	if (!sub_str)
		handle_malloc_error("expand variable");
	sub_str = expand_line(sub_str);
	end_str = ft_substr(str, *i + j + 1, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str));
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}

char	*if_quote(char *str, int *i)
{
	int		j;
	char	*sub_str;
	char	*end_str;

	j = 1;
	while (str[*i + j] != '\'')
		j++;
	sub_str = ft_substr(str, *i + 1, j - 1);
	if (!sub_str)
		handle_malloc_error("expand variable");
	end_str = ft_substr(str, *i + j + 1, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str));
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}

char	*if_normal(char *str, int *i)
{
	int	j;

	j = 0;
	while (str[*i + j] && str[*i + j] != '"' && str[*i + j] != '\'')
	{
		if (str[*i + j] == '$')
		{
			if (str[*i + j + 1] == '"' || str[*i + j + 1] == '\''
				|| str[*i + j + 1] == '{')
				return (*i += j, str);
			else
				break ;
		}
		j++;
	}
	if (str[*i + j] == '$')
	{
		while (str[*i + j] && str[*i + j] != '"' && str[*i + j] != '\''
			&& str[*i + 1] != '{')
		{
			if (str[*i + ++j] == '$')
				break ;
		}
	}
	return (normal_or_dollar(str, i, j));
}

char	*if_dollar(char *str, int *i)
{
	char	*end_str;
	int		j;

	j = 0;
	if (str[*i + 1] == '"' || str[*i + 1] == '\'')
	{
		end_str = ft_strdup(&str[*i] + 1);
		str[*i] = '\0';
		if (str[*i + 1] == '"')
			end_str = if_dquote(end_str, &j);
		else
			end_str = if_quote(end_str, &j);
		*i += j;
		str = ft_realloc(str, ft_strlen(end_str));
		ft_strcat(str, end_str);
		return (str);
	}
	if (str[*i + 1] == '{')
		return (if_cursh(str, i));
	else
		str = if_normal(str, i);
	return (str);
}

char	*expand_if_necessary(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			str = if_dquote(str, &i);
		else if (str[i] == '$')
			str = if_dollar(str, &i);
		else if (str[i] == '\'')
			str = if_quote(str, &i);
		else if (str[i] == '{')
			str = if_cursh(str, &i);
		else
			str = if_normal(str, &i);
	}
	return (str);
}
