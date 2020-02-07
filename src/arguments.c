/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:40:34 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/08 00:00:42 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void    check_flag(char *flag)
{
    if (!ft_strcmp(flag, "--Real_MODE") || !ft_strcmp(flag, "-R"))
        g_HEAD.real_mode = true;
    else
        error("args");
}

void			insert_arg(char *value)
{
	t_args  *last;
    t_args  *new_node;

    if (!(new_node = (t_args*)ft_memalloc(sizeof(t_args))))
        return ;
    new_node->value = ft_strdup(value);
    new_node->type = get_type(value);
    g_HEAD.argc += 1;
    if (g_HEAD.args == NULL)
    {
        new_node->prev = new_node;
        new_node->next = new_node;
        g_HEAD.args = new_node;
        g_HEAD.active_arg = &new_node;
        return ;
    }
    last = g_HEAD.args->prev;
    new_node->next = g_HEAD.args;
    g_HEAD.args->prev = new_node;
    new_node->prev = last;
}

void    get_args(char **av)
{
    int i;

    i = 0;
    g_HEAD.argc = 0;
    while (av[i])
    {
        insert_arg(av[i]);
        i++;
    }
    g_HEAD.selected_counter = 0;
}
