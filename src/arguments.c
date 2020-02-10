/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:40:34 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/09 21:03:23 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void    check_flag(char *flag)
{
    int key;

    key = 0;
    if (!ft_strcmp(flag, "-R"))
    {
        ft_putendl_fd("Are you sure you want to continue in Real Mode y/n?", 1);
        read(0, &key, 4);
        if ((char)key == Y_KEY)
            g_HEAD.real_mode = true;
        else
            g_HEAD.real_mode = false;
    }
    else
       error("args");
}

static void			insert_arg(char *value, int index)
{
	t_args  *last;
    t_args  *new_node;

    if (!(new_node = (t_args*)ft_memalloc(sizeof(t_args))))
        return ;
    new_node->value = ft_strdup(value);
    new_node->type = get_type(value);
    new_node->index = index;
    g_HEAD.argc += 1;
    if (g_HEAD.args == NULL)
    {
        new_node->prev = new_node;
        new_node->next = new_node;
        g_HEAD.args = new_node;
        g_HEAD.active_arg = &g_HEAD.args;
        return ;
    }
    last = g_HEAD.args->prev;
    new_node->next = g_HEAD.args;
    g_HEAD.args->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}
/*
void			insert_arg(char *value)
{
	t_args		*new;
	t_args		*last;

	new = (t_args *)ft_memalloc(sizeof(t_args));
	new->value = ft_strdup(value);
	new->type = get_type(value);
	g_HEAD.argc++;
	if (g_HEAD.args == NULL)
	{
		new->prev = new;
		new->next = new;
		g_HEAD.args = new;
		g_HEAD.active_arg = &g_HEAD.args;
		return ;
	}
	last = g_HEAD.args->prev;
	new->next = g_HEAD.args;
	g_HEAD.args->prev = new;
	new->prev = last;
	last->next = new;
}
*/
void    get_args(char **av)
{
    int i;

    i = 0;
    g_HEAD.argc = 0;
    while (av[i])
    {
        insert_arg(av[i], i);
        i++;
    }
    g_HEAD.selected_counter = 0;
}
