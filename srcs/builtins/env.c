/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:30:58 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 05:13:31 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	for_env(t_env *env)
{
	while (env)
	{
		if (env->global == GLOBAL)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
}

void	for_export(t_env *env)
{
	while (env)
	{
		if (env->global == GLOBAL)
		{
			printf("export %s", env->key);
			if (env->value)
				printf("=\"%s\"\n", env->value);
			else
				printf("\n");
		}
		env = env->next;
	}
}

void	print_env(t_env *env, int cas, t_data *info)
{
	if (cas == 1)
		for_env(env);
	if (cas == 2)
		for_export(env);
	info->status = EXIT_SUCCESS;
}
