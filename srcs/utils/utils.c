/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:58:26 by madamou           #+#    #+#             */
/*   Updated: 2024/10/10 18:14:48 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	ft_is_numeric(char *nb)
{
	int	i;

	i = 0;
	if (!nb)
		return (0);
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	while (nb[i])
	{
		if (ft_isdigit(nb[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	skip_white_space(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		++(*i);
}

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_free_2d(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		ft_free(split[i++]);
	ft_free(split);
	split = NULL;
}

void	for_pwd_and_oldpwd(t_data *data)
{
	t_env	*env;

	env = search_in_env("OLDPWD");
	if (!env)
	{
		env = init_env("OLDPWD", GLOBAL);
		add_back_env(&data->env, env);
	}
	env = search_in_env("PWD");
	if (!env)
	{
		env = init_env("PWD=", GLOBAL);
		add_back_env(&data->env, env);
	}
	ft_free(env->value);
	env->value = ft_pwd(GET, data);
}

void	set_pwd_and_shlvl(t_data *data)
{
	t_env	*env;

	for_pwd_and_oldpwd(data);
	env = search_in_env("SHLVL");
	if (!env)
	{
		env = init_env("SHLVL=1", GLOBAL);
		add_back_env(&data->env, env);
	}
	else
	{
		if (ft_is_numeric(env->value) && env->value[0] != '-')
			env->value = ft_sprintf("%d", ft_atoi(env->value) + 1);
		else if (ft_is_numeric(env->value) && env->value[0] == '-')
			env->value = ft_sprintf("%d", 0);
		else
			env->value = ft_sprintf("%d", 1);
	}
}
