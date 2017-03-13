/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:31:00 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:31:05 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			printable(t_env *v, t_term *b, t_com **list)
{
	t_com	*vag;
	t_com	*n;

	if (v == NULL || b == NULL || (n = (t_com *)malloc(sizeof(t_com))) == NULL)
		return (error(9));
	vag = *list;
	while (vag->u == 0)
		vag = vag->next;
	n->u = 0;
	n->h = 0;
	n->next = vag;
	if (vag->prev)
	{
		vag->prev->next = n;
		n->prev = vag->prev;
	}
	else
	{
		n->prev = NULL;
		*list = n;
	}
	vag->prev = n;
	n->c = b->buf[0];
	return (1);
}

int			mini_clear(t_com *com)
{
	if (com == NULL)
		return (error(0));
	while (com->c != -1)
	{
		com->h = 0;
		com->u = 0;
		com = com->next;
	}
	com->u = 1;
	return (1);
}

int			non_printable(t_env *v, t_term *b, t_com **l, int ret)
{
	t_com	*cp;

	if (v == NULL || b == NULL)
		return (error(0));
	cp = *l;
	if (ctrlr(v, b, l, 1) == 1 || arow(v, b, *l) == 1 || ft_delete(v, b, l) == 1
	|| control(v, b, *l) == 1 || shift(v, b, *l) == 1 || home_end(b, *l) == 1 ||
	xcv(v, b, l) == 1 || tabu(v, b, l) == 1)
		return (1);
	else if (b->buf[0] == 10 && check_reverse(v, l))
	{
		if ((*l) != NULL && (*l)->c == -1 && v->missin_q == 0)
			return (1);
		if ((ret = quotes(v, b, l)) == -2)
			set_list(l);
		else if (ret == 1)
		{
			get_prompt("MonTerm>");
			mini(v, l, cp, b);
			return (42);
		}
		else if (ret == -1)
			return (error(0));
	}
	return (-1);
}

int			treat(t_env *env, t_term *buf, t_com **list)
{
	int	ret;

	if (env == NULL || buf == NULL || list == NULL)
		return (error(0));
	ret = 0;
	if (ft_isprint(buf->buf[0]) == 1 && ft_strlen(buf->buf) == 1)
	{
		printable(env, buf, list);
		if (get_histo_r(-1) == 1)
			ctrlr(env, buf, list, 0);
		return (1);
	}
	ret = non_printable(env, buf, list, 0);
	return (ret);
}
