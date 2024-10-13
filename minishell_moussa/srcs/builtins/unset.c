/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:22:52 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 04:59:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	ft_unset(char **args, t_data *info)
{
	int		i;
	t_env	*env;

	i = 1;
	while (args[i])
	{
		env = info->env;
		while (env && ft_strcmp(args[i], env->key) != 0)
			env = env->next;
		if (env)
		{
			if (env->before)
				env->before->next = env->next;
			else
				info->env = env->next;
			if (env->next)
				env->next->before = env->before;
		}
		i++;
	}
	info->status = 0;
}
