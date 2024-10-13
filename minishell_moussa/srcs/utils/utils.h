/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:58:52 by madamou           #+#    #+#             */
/*   Updated: 2024/10/13 17:25:09 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../data/data.h"

void	skip_white_space(char *str, int *i);
void	ft_free_2d(char **split);
int		ft_strlen_2d(char **str);
char	**split_first_value(char *str, char sep);
void	add_string_char_2d(char ***tabb, char *str);
int		ft_is_numeric(char *nb);
int		all_char_are_the_same(char *str);
void	set_pwd_and_shlvl(t_data *info);
void printf_2d_array(char **to_print);

#endif
