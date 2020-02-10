/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:21:54 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/10 02:24:07 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	reset_terminal(void)
{
	tcsetattr(g_HEAD.glb_fd, TCSANOW, &g_HEAD.old_attribute);
	tputs(tgetstr("te", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
}

void	selecting(void)
{
	t_args *on;

	on = *g_HEAD.active_arg;
	on->is_on = !(on)->is_on;
	if (on->is_on == true)
	{
		g_HEAD.selected_counter++;
		g_HEAD.active_arg = &(*g_HEAD.active_arg)->next;
	}
	else
		g_HEAD.selected_counter--;
	return ;
}

void	up_(t_args **selected)
{
	t_args *node;
	int		i;
	int		index;
	int		incr;
	int no_cls;

	no_cls = count_colomns();
	node = *selected;
	index = node->index;
	incr = g_HEAD.argc - (g_HEAD.argc % no_cls);
	i = -1;
	if (index + incr < g_HEAD.argc)
	{
		while (node)
		{
			if (node->index == incr + index)
			{
				g_HEAD.active_arg = &node;
				return ;
			}
			node = node->next;
		}
	}
	else if (index < no_cls && (((g_HEAD.argc % no_cls) % index) == 0 ||
		(((g_HEAD.argc % no_cls) % index) == g_HEAD.argc % no_cls)))
		i -= 5;
	while (++i < no_cls)
		node = node->prev;
	g_HEAD.active_arg = &node;
}

void	down_(t_args **selected)
{
	t_args *node;
	int no_cls;
	int index;

	no_cls = count_colomns();
	node = *selected;
	index = node->index;
	if (index + no_cls >= g_HEAD.argc)
	{
		while (node)
		{
			if (node->index == index % no_cls)
			{
				g_HEAD.active_arg = &node;
				return ;	
			}
			node = node->next;
		}
	}
	no_cls = -1;
	while (++no_cls < count_colomns())
		node = node->next;
	g_HEAD.active_arg = &node;
}
