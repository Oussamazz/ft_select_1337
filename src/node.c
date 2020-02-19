/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 23:07:22 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/19 01:05:49 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			my_del(const char *fpath, const struct stat *sb,
	int typeflag, struct FTW *ftwbuf)
{
	int ret;

	(void)sb;
	(void)typeflag;
	(void)ftwbuf;
	ret = remove(fpath);
	return (ret);
}

void		delete_file(char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
		return ;
	if (S_ISDIR(sb.st_mode))
		nftw(path, my_del, 64, FTW_DEPTH | FTW_PHYS);
	else
		remove(path);
}

void		delete_item(void)
{
	t_args	*active;

	if (!g_head.active_arg)
		return ;
	active = *g_head.active_arg;
	if (active == g_head.args)
	{
		if (g_head.args->next == active)
			g_head.args = NULL;
		else
			g_head.args = active->next;
	}
	g_head.active_arg = &active->next;
	active->next->prev = active->prev;
	active->prev->next = active->next;
	if (g_head.real_mode)
		delete_file(active->value);
	ft_strdel(&active->value);
	free(active);
	active = NULL;
	g_head.argc--;
	if (g_head.argc == 0)
		signal_kill();
}

void		ft_push_ddl(char *value, int index)
{
	t_args	*last;
	t_args	*new_node;

	if (!(new_node = (t_args*)ft_memalloc(sizeof(t_args))))
		return ;
	new_node->value = ft_strdup(value);
	new_node->type = get_type(value);
	new_node->index = index;
	g_head.argc += 1;
	if (g_head.args == NULL)
	{
		new_node->prev = new_node;
		new_node->next = new_node;
		g_head.args = new_node;
		g_head.active_arg = &g_head.args;
		return ;
	}
	last = g_head.args->prev;
	new_node->next = g_head.args;
	g_head.args->prev = new_node;
	new_node->prev = last;
	last->next = new_node;
}
