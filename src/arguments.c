/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:40:34 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/19 02:11:23 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	check_flag(char *flag)
{
	int key;

	key = 0;
	if (!ft_strcmp(flag, "-R"))
	{
		ft_putendl_fd("Are you sure you want to continue in Real Mode y/n?",
			g_head.glb_fd);
		read(0, &key, 4);
		if ((char)key == Y_KEY)
			g_head.real_mode = true;
		else
			g_head.real_mode = false;
	}
	else
	{
		error_usage(0);
		reset_terminal();
		exit(1);
	}
}

void	get_args(char **av)
{
	int i;

	i = 0;
	g_head.argc = 0;
	while (av[i])
	{
		ft_push_ddl(av[i], i);
		i++;
	}
	g_head.selected_counter = 0;
}
