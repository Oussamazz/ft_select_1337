/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 22:34:12 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/07 22:33:24 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_putchar_term(int c)
{
	return (write(2, &c, 1));
}

t_type		get_type(char *data)
{
	char	*name;

	name = ft_strrchr(data, '/') ? ft_strrchr(data, '/') + 1 : data;
	if (ft_strlen(name) < 2)
		return (UNK_FILE);
	if (name[0] == '.')
		return (DOT_FILE);
	if (name[ft_strlen(name) - 1] == 'c' && name[ft_strlen(name) - 2] == '.')
		return (C_FILE);
	if (name[ft_strlen(name) - 1] == 'a' && name[ft_strlen(name) - 2] == '.')
		return (A_FILE);
	if ((name[ft_strlen(name) - 1] == 'o' && name[ft_strlen(name) - 2] == '.')
		|| !ft_strcmp(name, "a.out"))
		return (O_FILE);
	if (name[ft_strlen(name) - 1] == 'h' && name[ft_strlen(name) - 2] == '.')
		return (H_FILE);
	if (!ft_strcmp(name, "Makefile"))
		return (MAKE_FILE);
	return (UNK_FILE);
}

/*
static t_direction    direction_(long key)
{
	t_direction dir;

	dir = UNK_dir;
	if (key == UP_KEY)
		dir = UP_dir;
	if (key == DOWN_KEY)
		dir = DOWN_dir;
	if (key == LEFT_KEY)
		dir = LEFT_dir;
	if (key == RIGHT_KEY)
		dir = RIGHT_dir;
}

void	continue_(t_direction dir)
{
	if (dir == LEFT_dir)
		g_HEAD.args = g_HEAD.args->prev;
	else if (dir == RIGHT_dir)
		g_HEAD.args = g_HEAD.args->next;
	else if (dir == UP_dir)
		up_();
	else if (dir == DOWN_KEY)
		down_();
	return ;
}*/

void    ft_select_loop(void)
{
	long key;

	while (1337)
	{
		ft_show();
		key = 0;
		read(2, &key, sizeof(key));
		if (key == ENTER_KEY)
			return ;   //breaking;
		/*else if (key == ESC_KEY)
			signal_kill(); //signals handeling
		else if (key == SPACE_KEY)
			select_item(); //select one item;
		else if (key == STAR_KEY || key == DLT_ALL_KEY)
			select_all_args(key); // select all or unselect all;
		else if (key == BSP_KEY || key == DEL_KEY)
			delete_item_arg();  // deleting;
		else if (key == OPEN_KEY || key == BACK_KEY)
			browse(key); // open and back ;
			*/
			//continue_(direction_(key)); // Arrows;
	}
}
