#include "../includes/includes.h"
#include "data/data.h"
#include "environement/env.h"
#include "minishell_loop/minishell_loop.h"
#include "parsing/parsing.h"
#include <fcntl.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal = 0;
int	init_aliases(void);
void	init_history(void);
t_token *lexer_alias(t_data *data, char *command_line);
void	print_AST(t_token *command);

void mshrc(void)
{
	t_data *data;
	t_queue queue;
	char	*file;
	int		fd;

	data = get_data(NULL, GET);
	fd = open(MSHRC, O_RDONLY);
	if (fd == -1)
		return;
	file = read_file(fd);
	close(fd);
	queue.first = lexer_alias(data, file);
	if (queue.first == NULL)
		return ;
	if (parser(&queue) == EXIT_FAILURE)
			return ;
	// queue.first = create_ast(queue.first, 0);
	queue.first = create_ast_test(queue.first);
	// print_AST(queue.first);
	ft_free(file);
	start_exec(queue.first);
	return ;
}

t_data *get_data(t_data *data, int flag)
{
	static t_data *save;
	
	if (flag == SET)
		save = data;
	return (save);
}

void minishell(t_data *data)
{
	data->is_child = false;
	mshrc();
	loop_minishell(data);
}

void subminishell(t_data *data, char **argv)
{
	data->is_child = true;
	if (ft_strcmp(argv[1], "-c") != 0)
	{
		data->status = 2;
		ft_fprintf(STDERR_FILENO, "minishell: %s: invalid option\n", argv[1]);
		return ;
	}
	if (!argv[2])
	{
		data->status = 2;
		ft_fprintf(2, "%s: -c: option requires an argument\n", data->name);
		return ;
	}
	if (argv[3])
		data->name = argv[3];
	mshrc();
	subshell_routine(data, argv[2]);
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

    rl_bind_keyseq("\\e[A", arrow_handler);
    rl_bind_keyseq("\\e[B", arrow_handler);
	get_data(&data, SET);
	data.name = "minishell";
	data.status = 0;
	data.env = NULL;
	data.alias = NULL;
	data.env = env_in_struct(envp);
	set_pwd_and_shlvl(&data);
	init_history();
	if (argc == 1)
		minishell(&data);
	else
		subminishell(&data, argv);
	return (data.status);
}
