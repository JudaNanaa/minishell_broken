/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:01:22 by madamou           #+#    #+#             */
/*   Updated: 2024/10/17 00:09:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include <unistd.h>

void error_printf(char *command)
{
	t_data *data;

	data = get_data(NULL, GET);
	ft_fprintf(STDERR_FILENO, "%s: %s: ", data->name, command);
	perror("write error");
}

int	all_char_are_the_same(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] != str[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	if_option(char **args, int *i)
{
	int	j;

	j = 0;
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n'
		&& all_char_are_the_same(&args[*i][1]))
	{
		(*i)++;
		j++;
	}
	return (j);
}

int	loop_echo(char **args, int i)
{
	while (args[i])
	{
		if (ft_printf(args[i]) == -1)
			return (error_printf("echo"), 1);
		if (args[i + 1])
		{
			if (ft_printf(" ") == -1)
				return (error_printf("echo"), 1);
		}
		i++;
	}
	return (0);
}

void	ft_echo(char **args, t_data *data)
{
	int	i;

	data->status = 0;
	if (args[1])
	{
		i = 1;
		if (if_option(args, &i))
			data->status = loop_echo(args, i);
		else
		{
			data->status = loop_echo(args, i);
			if (printf("\n") == -1)
				return (error_printf("echo"));
		}
	}
	else
	{
		if (printf("\n") == -1)
			return (error_printf("echo"));
	}
}
