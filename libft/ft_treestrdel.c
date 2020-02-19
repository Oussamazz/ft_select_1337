/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treestrdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:53:06 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/19 02:09:46 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_treestrdel(char **str1, char **str2, char **str3)
{
	if (str1)
		ft_strdel(str1);
	if (str2)
		ft_strdel(str2);
	if (str3)
		ft_strdel(str3);
}
