/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:01:22 by madamou           #+#    #+#             */
/*   Updated: 2024/10/14 15:01:28 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

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

void	loop_echo(char **args, int i)
{
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putstr(" ");
		i++;
	}
}

void	ft_echo(char **args, t_data *info)
{
	int	i;

	if (args[1])
	{
		i = 1;
		if (if_option(args, &i))
			loop_echo(args, i);
		else
		{
			loop_echo(args, i);
			printf("\n");
		}
	}
	else
		printf("\n");
	info->status = 0;
}
