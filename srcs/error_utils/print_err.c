/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:05:52 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/10 16:51:45 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"
#include <unistd.h>

void	print_err(char *err, int erno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	err = replace_newline(err);
	if (erno == true)
	{
		perror(err);
	}
	else if (err != NULL)
	{
		ft_putendl_fd(err, STDERR_FILENO);
	}
}

void	error_log(char *error, int erno)
{
	static int	error_num = -1;
	int			error_log_fd;
	static char	*error_log_file = NULL;

	if (error_num == -1)
		return (error_log_file = error, ++error_num, (void)0);
	else if (error_log_file == NULL)
		return ;
	error_log_fd = open(error_log_file, O_WRONLY | O_APPEND, 0644);
	if (error_log_fd == -1)
		return ;
	if (++error_num != 1)
		ft_putstr_fd("\n\n", error_log_fd);
	ft_putnbr_fd(error_num, error_log_fd);
	ft_putstr_fd(".\n", error_log_fd);
	error = replace_newline(error);
	if (erno == true)
	{
		ft_putstr_fd(error, error_log_fd);
		ft_putstr_fd(": ", error_log_fd);
		ft_putendl_fd(strerror(errno), error_log_fd);
	}
	else if (error != NULL)
		ft_putendl_fd(error, error_log_fd);
	close(error_log_fd);
}

void	init_error_log(void)
{
	int		fd;
	char	*pwd;

	pwd = ft_malloc(sizeof(char *) * 1024); //
	if (pwd == NULL)						//
		return ;							//
	/*pwd =*/ getcwd(pwd, 2056);			// need ft_pwd (ft_getcwd)
	if (pwd[0] == '\0')
		return (error_log(NULL, false));
	pwd = ft_re_strjoin(pwd, "/.error_log");
	if (pwd == NULL)
		return (error_log(NULL, false));
	fd = open(pwd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (error_log(NULL, false));
	lock(pwd);
	error_log(pwd, false);
	close(fd);
}

void	malloc_failed(char *function)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (function != NULL)
	{
		ft_putstr_fd(function, STDERR_FILENO);
		ft_putstr_fd("(): ", STDERR_FILENO);
	}
	perror("Malloc failed");
}
