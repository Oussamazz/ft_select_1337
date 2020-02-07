/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:21:54 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/07 19:08:40 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void    reset_to_default_and_free(void)
{
    tcsetattr(STDERR_FILENO, TCSANOW, &g_HEAD.old_attribute);
    tputs(tgetstr("te", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
    close(g_HEAD.glb_fd);
    //free_all();
}
