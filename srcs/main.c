#include "../includes/includes.h"
#include "data/data.h"
#include "environement/env.h"
#include <unistd.h>

 volatile sig_atomic_t	g_signal = 0;


t_data *get_data(t_data *data, int flag)
{
	static t_data *save;
	
	if (flag == SET)
		save = data;
	return (save);
}

void minishell(t_data *data)
{
	data->is_child = NO;
	loop_minishell(data);
}

void subminishell(t_data *data, char **argv)
{
	data->is_child = YES;
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
	
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	get_data(&data, SET);
	data.name = "minishell";
	data.status = 0;
	data.env = NULL;
	data.env = env_in_struct(envp);
	set_pwd_and_shlvl(&data);
	if (argc == 1)
		minishell(&data);
	else
		subminishell(&data, argv);
	return (data.status);
}
