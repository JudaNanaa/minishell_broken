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
	if (ft_access(command) == true)
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
	if (ft_strchr(command, '/') && ft_access(command) == true)
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
	if (node->args[0] == NULL||ft_strcmp(node->args[0], ":") == 0)
		free_and_exit(EXIT_SUCCESS);
	if (ft_strcmp(node->args[0], "!") == 0)
		free_and_exit(EXIT_FAILURE);
	path = find_path(node->args[0], data);
	if (path == NULL)
	{
		ft_fprintf(2, "%s: %s: command not found\n", data->name, node->args[0]);
		free_and_exit(127);
	}
	envp = t_env_to_envp(data->env, GLOBAL);
	execve(path, node->args, envp);
	ft_fprintf(STDERR_FILENO, "Error execve\n");
	free_and_exit(-1);
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
	execve(argv[0], argv, envp);
}

void do_builtin(t_token *node)
{
	t_data *data;

	data = get_data(NULL,GET);
	if (ft_strcmp(node->args[0], "export") == 0)
		data->status = ft_export(data, node->args);
	if (ft_strcmp(node->args[0], "env") == 0)
		print_env(data->env, 1, data);
	if (ft_strcmp(node->args[0], "pwd") == 0)
		ft_pwd(PRINT, data);
	if (ft_strcmp(node->args[0], "echo") == 0)
		ft_echo(node->args, data);
	if (ft_strcmp(node->args[0], "unset") == 0)
		ft_unset(node->args, data);
	if (ft_strcmp(node->args[0], "cd") == 0)
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
	if (ft_strcmp(node->args[0], "exit") == 0)
	{
		(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
		(close(save_stdin), close(save_stdout));
		ft_exit(node->args);
	}
	do_builtin(node);
	(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
	(close(save_stdin), close(save_stdout));
}

void printf_2d_array(char **to_print)
{
	int i;

	i = 0;
	while (to_print[i])
	{
		ft_printf("%s\n", to_print[i]);
		i++;
	}
}

void	expand_cmd(t_token *cmd)
{
	int	i;
	int j;
	char *arg;
	char *check;


	if (cmd->args == NULL)
		return ;
	i = -1;
	j = 0;
	while (cmd->args[++i] != NULL)
	{
		check = ft_strdup(cmd->args[i]);
		arg = expand_if_necessary(cmd->args[i]);
		if (arg[0] == '\0' && !is_a_quotes(check[ft_strlen(check) - 1]))
			continue;
		cmd->args[j++] = arg;
		ft_free(check);
	}
	cmd->args[j] = NULL;
}

void exec(t_token *current)
{
	if (current->type == CMD)
	{
		expand_cmd(current);
		if (check_built_in(current->args[0]))
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

char	*find_path_cd(char *command)
{
	int		i;
	char	*path;
	char	**split;
	char	*value;

	i = 0;
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

int try_cd(char *directory)
{
	if (chdir(directory) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void single_command(t_token *node)
{
	char	*path;
	int status;
	int pid;

	if (node->type == SUBSHELL)
	{
		pid = ft_fork();
		if (pid == 0)
			exec_subshell(node);
		(waitpid(pid, &status, 0), exit_status(status));
	}
	else
	{
		path = find_path_cd(node->args[0]);
		if (path == NULL && !node->args[1])
		{
			if (try_cd(node->args[0]) == EXIT_SUCCESS)
				return;
		}
		pid = ft_fork();
		if (pid == 0)
			exec(node);
		(waitpid(pid, &status, 0), exit_status(status));
	}
}

void start_exec(t_token *node)
{
	t_data *data;
	struct termios	term;

	data = get_data(NULL, GET);
	set_exec(data, &term);
	if (data->is_child == false)
		set_signal_parent_exec();
	if ((node->type == CMD && check_built_in(node->args[0]) == false)
		|| node->type == SUBSHELL)
			single_command(node);
	else
		exec(node);
	after_exec(data, &term);
}
