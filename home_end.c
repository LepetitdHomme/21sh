/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:20:15 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 15:38:45 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		home_end(t_term *b, t_com *list)
{
	t_com	*tmp;

	if (b == NULL || list == NULL)
		return (error(0));
	tmp = list;
	while (tmp->c != -1 && tmp->u == 0)
		tmp = tmp->next;
	if (b->buf[0] == 27 && b->buf[1] == 91 && b->buf[2] == 72)
	{
		tmp->u = 0;
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->u = 1;
		return (1);
	}
	else if (b->buf[0] == 27 && b->buf[1] == 91 && b->buf[2] == 70)
	{
		tmp->u = 0;
		while (tmp->c != -1)
			tmp = tmp->next;
		tmp->u = 1;
		return (1);
	}
	return (-1);
}
