/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:57:08 by ibaby             #+#    #+#             */
/*   Updated: 2024/10/11 20:10:19 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	expand(t_token *ast)
{
	if (ast == NULL)
		return (EXIT_SUCCESS);
	if (ast->type == CMD)
		return (expand_cmd(ast));
	else if (is_operator_type(ast->type))
	{
		if (expand(ast->left) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (expand(ast->right) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	expand_cmd(t_token *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (0 /* wildcard expandable */)
			expand_wildcard(cmd);
		else if (0 /* env expandable */)
			expand_env(cmd);
		else if (0 /**/)
	}
}