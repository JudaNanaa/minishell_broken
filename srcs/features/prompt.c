/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:42:23 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/12 16:06:23 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"
// #include <cstddef>

char	*minishell_prompt(void)
{
	char	*prompt;
	char	*pwd;

	prompt = NULL;
	pwd = NULL;
	if (pwd == NULL)
		pwd = ft_getenv("PWD");
	if (pwd == NULL)
		return (urgency_prompt());
	prompt = add_arrow();
	if (prompt == NULL)
		return (urgency_prompt());
	prompt = add_dir_name(prompt);
	prompt = add_git_head(prompt);
	prompt = ft_re_strjoin(prompt, "\001\033[0m\002");
	if (prompt == NULL || *prompt == '\0')
		return (ft_free(prompt), urgency_prompt());
	return (prompt);
}

char	*add_dir_name(char *prompt)
{
	char	*dir;
	char	*temp;

	temp = ft_pwd(GET, get_data(NULL, GET));
	if (temp == NULL || ft_strchr(temp, '/') == NULL)
	{
		dir = ft_strjoin(prompt, "minishell ");
		if (dir == NULL)
			return (prompt);
		return (ft_free(prompt), dir);
	}
	if (ft_getenv("HOME") != NULL && ft_strcmp(ft_getenv("HOME"), temp) == 0)
		dir = ft_strdup("~ ");
	else if (*(ft_strrchr(temp, '/') + 1) == '\0')
		dir = ft_strdup("/ ");
	else
		dir = ft_strjoin(ft_strrchr(temp, '/') + 1, " ");
	if (dir == NULL)
		return (prompt);
	temp = ft_strjoin(prompt, dir);
	ft_free(dir);
	if (temp == NULL)
		return (prompt);
	return (ft_free(prompt), temp);
}

char	*add_git_head(char *prompt)
{
	char	*git;
	char	*temp;

	temp = git_head();
	if (temp == NULL)
		return (prompt);
	git = ft_sprintf(
		"\001\033[34;1m\002git:(\001\033[31;1m\002%s\001\033[34;1m\002) ", temp);
	ft_free(temp);
	if (git == NULL)
		return (prompt);
	temp = ft_strjoin(prompt, git);
	ft_free(git);
	if (temp == NULL)
		return (prompt);
	temp = add_git_delay(temp);
	return (ft_free(prompt), temp);
}

char	*add_git_delay(char *prompt)
{
	char	*head;

	head = git_head();
	if (head == NULL)
		return (prompt);
	if (is_delayed(head) != true)
		return (ft_free(head), prompt);
	ft_free(head);
	head = ft_strjoin(prompt, "\001\033[33;1m\002✗ ");
	if (head == NULL)
		return (prompt);
	return (ft_free(prompt), head);
}

char	*add_arrow(void)
{
	char	*color;
	char	*arrow;
	t_data	*data;

	data = get_data(NULL, GET);
	if (data->status == 0)
		color = "\001\033[32;5m\002";
	else
		color = "\001\033[31;5m\002";
	arrow = ft_strjoin(color, "➜  \001\033[0m\033[36;1m\002");
	if (arrow == NULL)
		return (NULL);
	return (arrow);
}
