/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:31:57 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 10:20:02 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	pp_plus(t_term *buf, t_com *tmp)
{
	t_com	*vag;
	t_com	*new;

	if (buf == NULL || tmp == NULL)
		return (error(0));
	if ((new = (t_com *)malloc(sizeof(t_com))) == NULL)
		return (error(9));
	new->c = tmp->c;
	new->u = tmp->u;
	new->h = 0;
	new->prev = NULL;
	new->next = NULL;
	if (buf->pp == NULL)
	{
		buf->pp = new;
		return (1);
	}
	vag = buf->pp;
	while (vag->next)
		vag = vag->next;
	vag->next = new;
	new->prev = vag;
	return (1);
}

static int	suppr(t_com **list, t_com **tmp)
{
	t_com	*suppr;

	if (list == NULL || *list == NULL || tmp == NULL || *tmp == NULL)
		return (error(0));
	if ((*tmp)->prev && (*tmp)->next)
	{
		(*tmp)->prev->next = (*tmp)->next;
		(*tmp)->next->prev = (*tmp)->prev;
		suppr = *tmp;
		*tmp = (*tmp)->next;
		free(suppr);
	}
	else if ((*tmp)->next && !(*tmp)->prev)
	{
		*list = (*tmp)->next;
		(*tmp)->next->prev = NULL;
		suppr = *tmp;
		*tmp = (*tmp)->next;
		free(suppr);
	}
	return (1);
}

static int	ft_coller(t_env *v, t_term *buf, t_com **list)
{
	t_com	*vag;
	t_com	*tmp;
	t_com	*retenue;

	if (v == NULL || buf == NULL || list == NULL || *list == NULL)
		return (error(0));
	if (buf->pp == NULL)
		return (1);
	vag = *list;
	tmp = buf->pp;
	while (vag->c != -1 && vag->u == 0)
		vag = vag->next;
	retenue = vag;
	ft_coller_tool(&vag, &tmp, list);
	while (tmp)
	{
		vag->next = new_com(tmp);
		tmp = tmp->next;
		vag->next->prev = vag;
		vag = vag->next;
	}
	vag->next = retenue;
	retenue->prev = vag;
	return (1);
}

static int	ft_couper(t_env *v, t_term *b, t_com **list, int i)
{
	t_com	*tmp;

	if (v == NULL || b == NULL || list == NULL || *list == NULL)
		return (error(0));
	if (b->pp != NULL && ft_free_l(b->pp) == 1)
		b->pp = NULL;
	tmp = *list;
	while (tmp && tmp->c != -1)
	{
		if (tmp->h == 1)
		{
			pp_plus(b, tmp);
			if (i == 1)
			{
				if (tmp->u == 1)
					tmp->next->u = 1;
				suppr(list, &tmp);
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

int			xcv(t_env *v, t_term *b, t_com **list)
{
	char	*c;

	if (list == NULL || *list == NULL || v == NULL || b == NULL)
		return (error(0));
	c = ft_strdup(b->buf);
	if (c[0] == 27 && c[1] == 120 && ft_couper(v, b, list, 1) == 1)
	{
		free(c);
		return (1);
	}
	if (c[0] == 27 && c[1] == 99 && ft_couper(v, b, list, 0) == 1)
	{
		free(c);
		return (1);
	}
	if (c[0] == 27 && c[1] == 118 && ft_coller(v, b, list) == 1)
	{
		free(c);
		return (1);
	}
	free(c);
	return (-1);
}
