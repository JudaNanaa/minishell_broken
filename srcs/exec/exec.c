/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:16:49 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 21:20:300 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../../includes/includes.h"
#include <unistd.h>

int	ft_access(char *path)
{
	int			check_stat;
	struct stat	sb;

	check_stat = stat(path, &sb);
	if (check_stat == -1)
		return (false);
	if (access(path, F_OK | X_OK) == 0 && S_ISREG(sb.st_mode))
		return (true);
	return (false);
}

void	if_potentialy_a_directory(char *command, t_data *data)
{
	struct stat	sb;
	int			check;

	check = stat(command, &sb);
	if (check == 0 && S_ISDIR(sb.st_mode))
	{
		ft_fprintf(2, "%s: %s: Is a directory\n", data->name, command);
		free_and_exit(126);
	}
	if (ft_access(command) == 0)
		return ;
	if (errno == EACCES)
	{
		ft_fprintf(2, "%s: %s: Permission denied\n", data->name, command);
		free_and_exit(126);
	}
	ft_fprintf(2, "%s: %s: No such file or directory\n", data->name, command);
	free_and_exit(127);
}

char	*find_path(char *command, t_data *data)
{
	int		i;
	char	*path;
	char	**split;
	char	*value;

	i = 0;
	if (ft_strchr(command, '/'))
		if_potentialy_a_directory(command, data);
	if (ft_strchr(command, '/') && ft_access(command) == 0)
		return (command);
	value = ft_getenv("PATH");
	if (value)
	{
		split = ft_split(value, ":");
		while (split[i])
		{
			path = ft_sprintf("%s/%s", split[i], command);
			if (ft_access(path) == true)
				return (ft_free_2d(split), path);
			(ft_free(path), i++);
		}
		ft_free_2d(split);
	}
	return (NULL);
}

void exec_cmd(t_token *node)
{
	t_data *data;
	char **envp;
	char	*path;

	data = get_data(NULL, GET);
	open_files(node);
	path = find_path(node->args[0], data);
	envp = t_env_to_envp(data->env, GLOBAL);
	if (path == NULL)
	{
		ft_fprintf(2, "%s: %s: command not found\n", data->name, node->args[0]);
		free_and_exit(127);
	}
	if (!ft_strcmp(node->args[0], "ls") || !ft_strcmp(node->args[0], "grep"))
		add_string_char_2d(&node->args, ft_strdup("--color=auto"));
	execve(path, node->args, envp);
}

void exec_subshell(t_token *node)
{
	char *argv[4];
	t_data *data;
	char **envp;

	data = get_data(NULL, GET);
	open_files(node);
	argv[0] = ft_strdup("./minishell");
	argv[1] = ft_strdup("-c");
	argv[2] = ft_strdup(node->content);
	argv[3] = NULL;
	envp = t_env_to_envp(data->env, GLOBAL);
	printf("const char *restrict format, ...\n");
	execve(argv[0], argv, envp);
}

void do_builtin(t_token *node)
{
	t_data *data;

	data = get_data(NULL,GET);
	if (ft_strcmp(node->content, "export") == 0)
		data->status = ft_export(data, node->args);
	if (ft_strcmp(node->content, "env") == 0)
		print_env(data->env, 1, data);
	if (ft_strcmp(node->content, "pwd") == 0)
		ft_pwd(PRINT, data);
	if (ft_strcmp(node->content, "echo") == 0)
		ft_echo(node->args, data);
	if (ft_strcmp(node->content, "unset") == 0)
		ft_unset(node->args, data);
	if (ft_strcmp(node->content, "cd") == 0)
		data->status = ft_cd(node->args[1]);
}

void exec_builtin(t_token *node)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (open_files(node) == EXIT_FAILURE)
		return;
	if (ft_strcmp(node->content, "exit") == 0)
	{
		(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
		(close(save_stdin), close(save_stdout));
		ft_exit(node->args);
	}
	do_builtin(node);
	(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
	(close(save_stdin), close(save_stdout));
}

void exec(t_token *current)
{
	if (current->type == CMD)
	{
		if (check_built_in(current->content))
			exec_builtin(current);
		else
			exec_cmd(current);
	}
	else if (current->type == SUBSHELL)
		exec_subshell(current);
	else if (current->type == AND)
		exec_and(current);
	else if (current->type == OR)
		exec_or(current);
	else if (current->type == PIPE)
		exec_pipe(current);
	else if (current->type == LIST)
		exec_list(current);
}

void	set_exec(t_data *data, struct termios *term)
{
	tcgetattr(STDOUT_FILENO, term);
	data->signaled = 0;
	if (data->is_child == 0)
		set_signal_parent_exec();
	else
		set_signal_child();
}

void after_exec(t_data *data, struct termios *term)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	check_if_signal(data);
}

void start_exec(t_token *node)
{
	int pid;
	t_data *data;
	int status;
	struct termios	term;

	data = get_data(NULL, GET);
	set_exec(data, &term);
	if (data->is_child == false)
		set_signal_parent_exec();
	if ((node->type == CMD && check_built_in(node->content) == false) || node->type == SUBSHELL)
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node);
		(waitpid(pid, &status, 0), exit_status(status));
	}
	else
		exec(node);
	after_exec(data, &term);
}
