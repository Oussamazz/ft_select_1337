/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 05:49:12 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/10 06:51:10 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void    free_all(void)
{
    t_args  *curr;
    t_args  *first;
    t_args  *tmp;

    first = g_HEAD.args;
    curr = first;
    while (curr)
    {
        ft_strdel(&curr->value);
        if (curr->next == first)
            break ;
        tmp = curr;
        curr = curr->next;
        free(tmp);
        tmp = NULL;
    }
    if (curr)
    {
        free(curr);
        curr = NULL;
    }
    g_HEAD.args = NULL;
}