/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 15:29:18 by csellier          #+#    #+#             */
/*   Updated: 2017/03/15 14:18:53 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	first_arrow(t_env *v, t_term *b, t_com *vag)
{
	if (v == NULL || b == NULL || vag == NULL)
		return (-1);
	if (vag->prev)
	{
		vag->u = 0;
		vag->prev->u = 1;
	}
	return (1);
}

static int	second_arrow(t_env *v, t_term *b, t_com *vag)
{
	if (v == NULL || b == NULL || vag == NULL)
		return (-1);
	if (vag->next)
	{
		vag->u = 0;
		vag->next->u = 1;
	}
	return (1);
}

static int	third_arrow(t_env *v, t_term *b, t_com *vag)
{
	t_histo	*h;

	if (v == NULL || b == NULL || vag == NULL)
		return (-1);
	if (v->histo == NULL || v->c_histo == NULL)
		return (1);
	h = v->c_histo;
	while (h && h->affich == 0)
		h = h->next;
	if (h && h->prev)
	{
		vag->u = 0;
		while (vag->c != -1)
			vag = vag->next;
		vag->u = 1;
		h->affich = 0;
		h->prev->affich = 1;
	}
	return (1);
}

static int	fourth_arrow(t_env *v, t_term *b, t_com *vag)
{
	t_histo	*h;

	if (v == NULL || b == NULL || vag == NULL)
		return (-1);
	if (v->histo == NULL || v->c_histo == NULL)
		return (1);
	h = v->c_histo;
	while (h && h->affich == 0)
		h = h->next;
	if (h && h->next)
	{
		vag->u = 0;
		while (vag->c != -1)
			vag = vag->next;
		vag->u = 1;
		h->affich = 0;
		h->next->affich = 1;
	}
	return (1);
}

int			arow(t_env *env, t_term *buf, t_com *l)
{
	t_com	*vag;

	if (buf == NULL || env == NULL || l == NULL)
		return (error(0));
	vag = l;
	while (vag && vag->u == 0)
		vag = vag->next;
	if (buf->buf[0] == 27 && buf->buf[1] == 91 && buf->buf[2] == 68)
		return (first_arrow(env, buf, vag));
	else if (buf->buf[0] == 27 && buf->buf[1] == 91 && buf->buf[2] == 67)
		return (second_arrow(env, buf, vag));
	else if (buf->buf[0] == 27 && buf->buf[1] == 91 && buf->buf[2] == 66)
		return (third_arrow(env, buf, vag));
	else if (buf->buf[0] == 27 && buf->buf[1] == 91 && buf->buf[2] == 65)
		return (fourth_arrow(env, buf, vag));
	return (-1);
}
