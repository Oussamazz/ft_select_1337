/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 23:07:22 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/07 23:33:26 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_append(char *data)
{
   t_args *last;
   t_args *new;

   if (!(new = (t_args*)ft_memalloc(sizeof(t_args))))
	return ;
	new->value = ft_strdup(data);
	new->type = get_type(data);
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
