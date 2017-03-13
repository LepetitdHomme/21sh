/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 18:43:56 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 16:18:56 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		concat_lst(t_env *v, t_com *end)
{
	t_com	*vag;

	if (end == NULL || v == NULL)
		return (error(0));
	if (v->begin == NULL)
	{
		if ((v->begin = copy_lst(end)) == NULL)
			return (error(13));
		return (1);
	}
	vag = v->begin;
	while (vag && vag->next && vag->next->c != -1)
		vag = vag->next;
	free(vag->next);
	vag->next = NULL;
	if ((vag->next = copy_lst(end)) == NULL)
		return (error(13));
	vag->next->prev = vag;
	return (1);
}

t_com	*copy_lst(t_com *l)
{
	t_com	*vag;
	t_com	*r;

	if ((l == NULL || (r = (t_com *)malloc(sizeof(t_com))) == NULL) && error(9))
		return (NULL);
	vag = r;
	r->c = l->c;
	r->u = l->u;
	r->h = l->h;
	r->prev = l->prev;
	r->next = NULL;
	l = l->next;
	while (l)
	{
		if ((r->next = (t_com *)malloc(sizeof(t_com))) == NULL && error(9))
			return (NULL);
		r->next->c = l->c;
		r->next->u = l->u;
		r->next->h = l->h;
		r->next->prev = r;
		r->next->next = NULL;
		l = l->next;
		r = r->next;
	}
	return (vag);
}
