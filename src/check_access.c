/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:55:38 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/17 15:20:11 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		check_access(char *path)
{
	if (access(path, R_OK) == 0)
		return (1);
	return (0);
}

void	ft_select_loop_(int key)
{
	if (key == SPACE_KEY)
		selecting();
	else if (key == STAR_KEY || key == DLT_ALL_KEY)
		un__select_all(key);
	else if (key == ESC_KEY)
		signal_kill();
	else if (key == BSP_KEY || key == DEL_KEY)
		delete_item();
	return ;
}
