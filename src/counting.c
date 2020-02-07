/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:45:55 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/07 23:50:38 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		count_colomns(void)
{
	int cols;

	cols = window_size(1) / (biggest_len_arg(g_HEAD.args) + 1);
	if (!cols)
		cols = 1;
	if ((biggest_len_arg(g_HEAD.args) + 1) * g_HEAD.argc < window_size(1))
		cols = g_HEAD.argc;
	return (cols);
}

int		window_size(int width_height)
{
	struct winsize	w_size;

	ioctl(g_HEAD.glb_fd, TIOCGWINSZ, &w_size);
	if (width_height)
		return ((int)w_size.ws_col);
	return ((int)w_size.ws_row);
}

size_t      biggest_len_arg(t_args *head)
{
	t_args	*first;
	t_args	*curr;
	size_t	ret;
	size_t	len;

	if (!g_HEAD.args || !(g_HEAD.args->value))
		return -1;
	first = g_HEAD.args;
	curr = first;
	ret = 0;
	while (curr)
	{
		len = ft_strlen((const char*)curr->value);
		ret = len > ret ? len : ret;
		if (curr->next == first)
			break ;
		curr = curr->next;
	}
	return (ret);
}
