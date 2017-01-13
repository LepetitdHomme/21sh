/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 09:34:53 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 15:37:24 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	right_n_left(t_com *l, char *c, t_com *cp)
{
	if (l == NULL || c == NULL)
		return (error(0));
	if (c[5] == 67)
	{
		while (cp->c != -1 && ft_isprint(cp->c) && ft_space(cp->c) != 1)
			cp = cp->next;
		while (cp->c != -1 && ft_space(cp->c) == 1)
			cp = cp->next;
	}
	else if (c[5] == 68 && cp->prev)
	{
		cp = cp->prev;
		while (cp && cp->prev && ft_space(cp->c) == 1)
			cp = cp->prev;
		while (cp->prev && ft_isprint(cp->c) && ft_space(cp->c) != 1)
			cp = cp->prev;
		if (cp->prev)
			cp = cp->next;
	}
	if (cp)
	{
		l->u = 0;
		cp->u = 1;
	}
	return (1);
}

static int	up_n_down(char *c, t_term *buf, t_com *l, t_com *cp)
{
	int		col;

	if (buf == NULL || l == NULL || cp == NULL)
		return (error(0));
	if (buf->count_cr < 1)
		return (1);
	col = buf->w_col;
	while (cp && col > 0)
	{
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

int			control(t_env *v, t_term *b, t_com *l)
{
	t_com	*cp;

	if (v == NULL || b == NULL || l == NULL)
		return (error(0));
	while (l->c != -1 && l->u == 0)
		l = l->next;
	cp = l;
	if (b->buf[0] == 27 && b->buf[1] == 91 && b->buf[2] == 49 &&
			b->buf[3] == 59 && b->buf[4] == 57)
	{
		if (b->buf[5] == 67 || b->buf[5] == 68)
			right_n_left(l, &b->buf[0], cp);
		else if (b->buf[5] == 66 || b->buf[5] == 65)
			up_n_down(&b->buf[0], b, l, cp);
		return (1);
	}
	return (-1);
}
