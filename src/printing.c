/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:16:37 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/19 01:48:11 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_putchar_term(int c)
{
	return (write(g_head.glb_fd, &c, 1));
}

void		print_selected_items(void)
{
	int		i;
	t_args	*curr;
	t_args	*first;

	first = g_head.args;
	curr = g_head.args;
	i = 0;
	while (curr)
	{
		if (curr->is_on)
		{
			ft_putstr_fd(curr->value, 1);
			i++;
			if (i < g_head.selected_counter)
				ft_putchar_fd(' ', 1);
		}
		if (curr->next == first)
			break ;
		curr = curr->next;
	}
}

static void	put_value_with_color(t_args *head)
{
	int fd;

	fd = g_head.glb_fd;
	if (head->type == H_FILE)
		ft_putstr_fd(T_H_COLOR, fd);
	else if (head->type == DIR_FILE)
		ft_putstr_fd(T_DIR_COLOR, fd);
	else if (head->type == A_FILE)
		ft_putstr_fd(T_A_COLOR, fd);
	else if (head->type == O_FILE)
		ft_putstr_fd(T_O_COLOR, fd);
	else if (head->type == MAKE_FILE)
		ft_putstr_fd(T_MAKEFILE_COLOR, fd);
	ft_putstr_fd(head->value, fd);
	ft_putstr_fd(DEFAULT_COLOR, fd);
}

void		print_list(int rows, int colomns, t_args *head, t_args *first)
{
	int		i;
	int		j;
	int		len;

	len = 0;
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < colomns)
		{
			if (head == (*g_head.active_arg))
				ft_putstr_fd(UNDERLINED, g_head.glb_fd);
			if (head->is_on)
				ft_putstr_fd(REVERSE_VIDEO_COLOR, g_head.glb_fd);
			put_value_with_color(head);
			len = ft_strlen(head->value);
			while (len++ <= biggest_len_arg())
				ft_putchar_fd(' ', g_head.glb_fd);
			if (head->next == first)
				break ;
			head = head->next;
		}
		ft_putchar_fd('\n', g_head.glb_fd);
	}
}

void		ft_show(void)
{
	int rows;
	int	colomns;
	int biggest_arg;

	biggest_arg = biggest_len_arg();
	if ((biggest_arg) > window_size(1))
	{
		tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
		return (ft_putendl_fd("Window size is too small!", g_head.glb_fd));
	}
	tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
	colomns = count_colomns();
	rows = g_head.argc / colomns;
	if (rows + 2 > window_size(0))
	{
		tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
		return (ft_putendl_fd("Window size is too small!", g_head.glb_fd));
	}
	if (g_head.argc % colomns)
		rows++;
	print_list(rows, colomns, g_head.args, g_head.args);
}
