/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 09:32:21 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 15:37:28 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	right_n_left(t_com *l, char *c, t_com *cp)
{
	if (l == NULL || c == NULL || cp == NULL)
		return (error(0));
	if (c[5] == 67 && cp->c != -1)
	{
		cp->h = (cp->h == 1) ? 0 : 1;
		cp = cp->next;
	}
	else if (c[5] == 68 && cp->prev)
	{
		cp->h = (cp->h == 1) ? 0 : 1;
		cp = cp->prev;
	}
	if (cp)
	{
		l->u = 0;
		cp->u = 1;
	}
	return (1);
}

static int	up_n_down(t_term *buf, t_com *l, char *c, t_com *cp)
{
	int	col;

	if (buf == NULL || l == NULL || c == NULL || cp == NULL)
		return (error(0));
	if (buf->count_cr < 1)
		return (1);
	col = buf->w_col;
	while (cp && col > 0)
	{
		cp->h = (cp->h == 0) ? 1 : 0;
		if (c[5] == 65 && cp)
			cp = cp->prev;
		else if (c[5] == 66 && cp->c != -1)
			cp = cp->next;
		col--;
	}
	if (cp)
	{
		l->u = 0;
		cp->u = 1;
	}
	return (1);
}

int			shift(t_env *env, t_term *b, t_com *list)
{
	t_com	*cp;

	if (env == NULL || b == NULL || list == NULL)
		return (error(0));
	while (list->c != -1 && list->u == 0)
		list = list->next;
	cp = list;
	if (b->buf[0] == 27 && b->buf[1] == 91 && b->buf[2] == 49 &&
			b->buf[3] == 59 && b->buf[4] == 50)
	{
		if (b->buf[5] == 68 || b->buf[5] == 67)
			right_n_left(list, &b->buf[0], cp);
		if (b->buf[5] == 66 || b->buf[5] == 65)
			up_n_down(b, list, &b->buf[0], cp);
		return (1);
	}
	return (-1);
}
