/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:27:01 by madamou           #+#    #+#             */
/*   Updated: 2024/12/16 15:18:53 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	error_message_file(char *content)
{
	t_data	*data;
	char	*message;

	data = get_data(NULL, GET);
	message = ft_sprintf("%s: %s", data->name, content);
	perror(message);
	ft_free(message);
	data->status = 1;
}

void ft_dup2(int newfd, int oldfd)
{
	t_data *data;

	data = get_data(NULL, GET);
	if (dup2(newfd, oldfd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s: Error when trying to dup2", data->name);
		free_and_exit(-1);
	}
}

int print_ambiguous_redir(char *wildcard)
{
	t_data *data;

	data = get_data(NULL, GET);
	ft_fprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
		data->name, wildcard);
	if (data->is_child == true)
		free_and_exit(1);
	return (EXIT_FAILURE);
}

int expand_file_path(t_file *file)
{
	char *path;
	t_data *data;
	char **wcards;
	char *check;

	check = ft_strdup(file->path);
	file->path = expand_if_tilde(file->path);
	data = get_data(NULL, GET);
	path = expand_str(ft_strdup(file->path));
	if (path[0] == '\0')
	{
		ft_fprintf(2, "%s: %s: ambiguous redirect\n", data->name, file->path);
		if (data->is_child == true)
			free_and_exit(1);
		return (EXIT_FAILURE);
	}
	if (!(is_a_quotes(check[ft_strlen(check) - 1]) || ft_strchr(path, '*') == NULL))
	{
		wcards = expand_wildcards(path);
		if (ft_strlen_2d(wcards) > 1)
			return (print_ambiguous_redir(path));
		path = wcards[0];
	}
	file->path = path;
	return (EXIT_SUCCESS);
}

int open_infile(t_file *file)
{
	int infile;
	t_data *data;

	data = get_data(NULL, GET);
	if (expand_file_path(file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	infile = open(file->path, O_RDONLY);
	if (infile == -1)
	{
		error_message_file(file->path);
		if (data->is_child == true)
			free_and_exit(1);
		return (EXIT_FAILURE);
	}
	ft_dup2(infile, STDIN_FILENO);
	close(infile);
	return (EXIT_SUCCESS);
}

int open_outfile(t_file *file, int open_mode)
{
	int outfile;
	t_data *data;

	data = get_data(NULL, GET);
	if (expand_file_path(file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	outfile = open(file->path, O_WRONLY | O_CREAT | open_mode, 0644);
	if (outfile == -1)
	{
		error_message_file(file->path);
		if (data->is_child == true)
			free_and_exit(1);
		return (EXIT_FAILURE);
	}
	ft_dup2(outfile, STDOUT_FILENO);
	close(outfile);
	return (EXIT_SUCCESS);
}

int	open_heredoc(t_file *file)
{
	int fd[2];
	int	i;
	t_data *data;

	i = -1;
	data = get_data(NULL, GET);
	if (pipe(fd) == -1)
	{
		error_message_file(file->path);
		if (data->is_child == true)
			free_and_exit(1);
		return (EXIT_FAILURE);
	}
	if (file->heredoc_content != NULL)
	{
		if (file->expand_heredoc == true)
		{
			while (file->heredoc_content[++i])
				ft_putendl_fd(expand_str(file->heredoc_content[i]), fd[1]);
		}
		else
		{
			while (file->heredoc_content[++i])
				ft_putendl_fd(file->heredoc_content[i], fd[1]);
		}
	}
	close(fd[1]);
	ft_dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (EXIT_SUCCESS);
}


int open_files(t_token *node)
{
	t_file *files;
	int result;

	files = node->files;
	while (files)
	{
		if (files->mode == INFILE)
			result = open_infile(files);
		else if (files->mode == HEREDOC || files->mode == HERESTRING)
			result = open_heredoc(files);
		else if (files->mode == OUT_TRUNC)
			result = open_outfile(files, O_TRUNC);
		else if (files->mode == OUT_APP)
			result = open_outfile(files, O_APPEND);
		if (result == EXIT_FAILURE)
			return (EXIT_FAILURE);
		files = files->next;
	}
	return (EXIT_SUCCESS);
}

void	exit_status(int status)
{
	t_data *data;

	data = get_data(NULL, GET);
	if (WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
		data->signaled = 1;
	}
	else if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	else if (WIFSTOPPED(status))
		data->status = 128 + WSTOPSIG(status);
}

void upgrade_shlvl(void)
{
	t_env	*env;

	env = search_in_env("SHLVL");
	if (env)
	{
		if (ft_is_numeric(env->value) && env->value[0] != '-'
			&& ft_atoi(env->value))
			env->value = ft_sprintf("%d", ft_atoi(env->value) - 1);
		else if (ft_is_numeric(env->value) && env->value[0] == '-')
			env->value = ft_sprintf("%d", 0);
		else
			env->value = ft_sprintf("%d", 0);
		lock(env->value);
	}
}

int ft_fork(void)
{
	int pid;
	t_data *data;

	data = get_data(NULL, GET);
	pid = fork();
	if (pid == -1)
		free_and_exit(-1);
	if (pid == 0)
	{
		data->is_child = YES;
		set_signal_child();
		upgrade_shlvl();
	}
	return (pid);
}

int	check_built_in(char *command)
{
	if (command == NULL)
		return (0);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "exit") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command, "alias") == 0)
		return (1);
	else if (ft_strcmp(command, "source") == 0)
		return (1);
	return (0);
}

void exec_pipe(t_token *node)
{
	int fd[2];
	int pid[2];
	int status;
	
	if (pipe(fd) == -1)
		free_and_exit(-1);
	pid[0] = ft_fork();
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(close(fd[0]), close(fd[1]));
		exec(node->left);
		free_and_exit(get_data(NULL, GET)->status);
	}
	pid[1] = ft_fork();
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		exec(node->right);
		free_and_exit(get_data(NULL, GET)->status);
	}
	(close(fd[0]), close(fd[1]));
	(waitpid(pid[0], &status, 0), exit_status(status));
	(waitpid(pid[1], &status, 0), exit_status(status));
}

void	fork_and_exec(t_token *node)
{
	int	pid;
	int	status;

	pid = ft_fork();
	if (pid == 0)
		exec(node);
	(waitpid(pid, &status, 0), exit_status(status));
}

int	check_if_fork(t_token *node)
{
	if (node->type == LOCAL_VAR)
		return (0);
	if ((node->type == CMD && !check_built_in(node->content))
		|| node->type == SUBSHELL)
		return (1);
	return (0);
}

void exec_and(t_token *node)
{
	t_data *data;

	data = get_data(NULL, GET);
	if (check_if_fork(node->left))
		fork_and_exec(node->left);
	else
		exec(node->left);
	if (data->status == 0)
	{
		if (check_if_fork(node->right))
			fork_and_exec(node->right);
		else
			exec(node->right);
	}	
}

void exec_or(t_token *node)
{
	t_data *data;

	data = get_data(NULL, GET);
	if (check_if_fork(node->left))
		fork_and_exec(node->left);
	else
		exec(node->left);
	if (data->status == 128 + SIGQUIT && data->is_child == false)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		data->signaled = 0;
	}
	if (data->status != 0 && data->status != 128 + SIGINT)
	{
		if (data->is_child == 1 && data->status == 128 + SIGQUIT)
			return ;
		if (data->status != 0)
		{
			if (check_if_fork(node->right))
				fork_and_exec(node->right);
			else
				exec(node->right);
		}
	}	
}

void exec_list(t_token *node)
{
	if (node->left)
	{
		if (check_if_fork(node->left))
			fork_and_exec(node->left);
		else
			exec(node->left);
	}
	if (node->right)
	{
		if (check_if_fork(node->right))
			fork_and_exec(node->right);
		else
			exec(node->right);
	}
}


int	is_a_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

