/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 18:43:56 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:36:25 by csellier         ###   ########.fr       */
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

t_com	*copy_lst(t_com *list)
{
	t_com	*vag;
	t_com	*r;

	if (list == NULL || (r = (t_com *)malloc(sizeof(t_com))) == NULL)
		error(9);
	vag = r;
	r->c = list->c;
	r->u = list->u;
	r->h = list->h;
	r->prev = list->prev;
	r->next = NULL;
	list = list->next;
	while (list)
	{
		if ((r->next = (t_com *)malloc(sizeof(t_com))) == NULL && error(9))
			return (NULL);
		r->next->c = list->c;
		r->next->u = list->u;
		r->next->h = list->h;
		r->next->prev = r;
		r->next->next = NULL;
		list = list->next;
		r = r->next;
	}
	return (vag);
}
