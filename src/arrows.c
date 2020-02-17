/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:21:54 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/16 23:01:43 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	un__select_all(int key)
{
	int		flag;
	t_args *curr;
	t_args *first;

	first = g_HEAD.args;
	curr = first;
	g_HEAD.selected_counter = 0;
	while (curr)
	{
		flag = (key == STAR_KEY ? 1 : 0);
		curr->is_on = flag;
		g_HEAD.selected_counter += flag;
		if (flag == 0)
			g_HEAD.selected_counter--;
		if (curr->next == first)
			break ;
		curr = curr->next;
	}
}

void	selecting(void)
{
	t_args *on;

	on = *g_HEAD.active_arg;
	(*g_HEAD.active_arg)->is_on = !(on)->is_on;
	if (on->is_on == true)
	{
		g_HEAD.selected_counter++;
		g_HEAD.active_arg = &(*g_HEAD.active_arg)->next;
	}
	else
		g_HEAD.selected_counter--;
	return ;
}

void	up_(void)
{
	t_args 	*node;
	t_args 	*first;
	int		index;
	int		no_cls;

	no_cls = count_colomns();
	node = *g_HEAD.active_arg;
	first = node;
	index = node->index;
	if (index - no_cls < 0)
		return (ft_putstr_fd("\a", 2));
	index = -1;
	while (++index + 1 < no_cls)
		node = node->prev;
	g_HEAD.active_arg = &node->prev;
}

void	down_(void)
{
	t_args	*node;
	t_args	*first;
	int		no_cls;
	int		index;

	no_cls = count_colomns();
	node = *g_HEAD.active_arg;
	index = node->index;
	first = node;
	if (index + no_cls >= g_HEAD.argc)
		return (ft_putstr_fd("\a", 2));
	no_cls = -1;
	while (++no_cls + 1 < count_colomns())
		node = node->next;
	g_HEAD.active_arg = &node->next;
}
