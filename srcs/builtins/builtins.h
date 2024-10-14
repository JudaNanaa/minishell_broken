/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:17:37 by madamou           #+#    #+#             */
/*   Updated: 2024/10/14 23:51:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# ifdef MINISHELL_H
#  undef MINISHELL_H
# endif

// # include "../../includes/includes.h"
# include "../data/data.h"

int		ft_cd(char *directory);
void	ft_echo(char **args, t_data *info);
int		ft_export(t_data *info, char **content);
void	print_env(t_env *env, int cas, t_data *info);
char	*ft_pwd(int cas, t_data *info);
void	ft_exit(char **args);
void	ft_unset(char **args, t_data *info);
void	print_exit(t_data *data);


// Alias
char	*ft_getalias(char *key);
int	ft_alias(t_data *data, char **content);

// PWD
# define PRINT 2

#endif // !BUILTINS_H
