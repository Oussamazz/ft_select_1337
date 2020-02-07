/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:16:37 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/08 00:03:34 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		put_value_with_color(t_args *head)
{
	int fd;

	fd = g_HEAD.glb_fd;
	/*if (head->type == A_FILE)
		ft_putstr_fd(T_A_COLOR, fd);
	if (head->type == O_FILE)
		ft_putstr_fd(T_O_COLOR, fd);*/
		//ft_putstr_fd(DEFAULT_COLOR, fd);
	ft_putstr_fd(head->value, fd);
}

static void		print_list(t_args *head)
{
	t_args *first;
	int i;
	int j;
	int len;

	len = 0;
	i = -1;
	first = head;
	while (++i < g_HEAD.rows)
	{
		j = -1;
		while (++j < g_HEAD.colomns)
		{
			if (g_HEAD.args->is_on)
				ft_putstr_fd(REVERSE_VIDEO_COLOR, g_HEAD.glb_fd);
			if (head == *g_HEAD.active_arg)
				ft_putstr_fd(UNDERLINED, g_HEAD.glb_fd);
			ft_putchar_fd('\n', g_HEAD.glb_fd);
			put_value_with_color(head);
			ft_putchar_fd(' ', g_HEAD.glb_fd);
			if (head->next == first)
				break ;
			head = head->next;
		}
	}
}

void			ft_show(void)
{
	int biggest_arg;

	biggest_arg = biggest_len_arg(g_HEAD.args);
	if ((biggest_arg) > window_size(1))
		return (ft_putendl_fd("Window size is too small! [W]", g_HEAD.glb_fd));
	tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
	g_HEAD.colomns = count_colomns();
	g_HEAD.rows = g_HEAD.argc / g_HEAD.colomns;
	if (g_HEAD.rows > window_size(0))
		return (ft_putendl_fd("Window size is too small! [H]", g_HEAD.glb_fd));
	if (g_HEAD.argc % g_HEAD.colomns)
		g_HEAD.rows++;
	ft_putchar_fd(' ', g_HEAD.glb_fd);
	ft_putnbr_fd(g_HEAD.colomns, g_HEAD.glb_fd);
	ft_putchar_fd(' ', g_HEAD.glb_fd);
	ft_putnbr_fd(g_HEAD.rows, g_HEAD.glb_fd);
	print_list(g_HEAD.args);
}
