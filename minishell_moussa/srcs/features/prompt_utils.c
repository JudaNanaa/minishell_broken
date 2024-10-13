/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:53:22 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 22:55:34 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "features.h"

char	*git_line(char *git_file)
{
	char	*path;
	char	*temp;
	int		i;

	i = -1;
	path = ft_strdup(".git/");
	if (path == NULL)
		return (NULL);
	while (access(path, X_OK) != 0)
	{
		if (++i > 20)
			return (NULL);
		temp = path;
		path = ft_strjoin("../", path);
		ft_free(temp);
		if (path == NULL)
			return (NULL);
	}
	path = ft_re_strjoin(path, git_file);
	if (path == NULL)
		return (NULL);
	i = open(path, O_RDONLY);
	if (i == -1)
		return (error_log("git_line: open(): ", true), ft_free(path), NULL);
	return (temp = get_next_line(i), close(i), ft_free(path), temp);
}

char	*git_head(void)
{
	char	*git;
	char	*temp;

	temp = git_line("HEAD");
	if (temp == NULL)
		return (NULL);
	temp = ft_strtrim(temp, "\n");
	if (temp == NULL)
		return (NULL);
	if (ft_strrchr(temp, '/') == NULL)
		return (ft_free(temp), NULL);
	git = ft_strrchr(temp, '/') + 1;
	if (*git == '\0')
		return (NULL);
	return (git);
}

/*
0: not delayed
1: delayed
-1: error
*/

int	is_delayed(char *head)
{
	char	*local;
	char	*remote;

	local = ft_strjoin("refs/heads/", head);
	if (local == NULL)
		return (-1);
	local = git_line(local);
	if (local == NULL)
		return (-1);
	remote = ft_strjoin("refs/remotes/origin/", head);
	if (remote == NULL)
		return (-1);
	remote = git_line(remote);
	if (remote == NULL)
		return (-1);
	if (ft_strcmp(local, remote) == 0)
		return (false);
	else
		return (true);
}

char	*urgency_prompt(void)
{
	char	*prompt;

	prompt = add_arrow();
	if (prompt == NULL)
		return (NULL);
	prompt = ft_re_strjoin(prompt, "minishell \001\033[0m\002");
	return (prompt);
}
