/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:56:06 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 16:59:03 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"

int	errcode(int errcode, bool setter)
{
	static int	code = 0;

	if (setter == false)
		return (code);
	else
		return (code = errcode);
}
