/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:24:00 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/09 19:22:30 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	error(char *error_type)
{
	if (!ft_strcmp(error_type, "TERM"))
		env_TERM();
	else if (!ft_strcmp(error_type, "fd"))
		ft_putendl_fd("Error: Can't open or/and read /dev/tty", 2);
	else if (!ft_strcmp(error_type, "args"))
		error_usage();
	exit(EXIT_FAILURE);
}

void	error_usage(void)
{
	ft_putendl_fd("Usage ./ft_select -[R] [arg1 arg2...]", 2);
	return ;
}

void	env_TERM(void)
{
	ft_putendl_fd("Error: TERM variable not found.", 2);
	return ;
}
