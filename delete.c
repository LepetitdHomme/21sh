/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 14:48:38 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 15:14:51 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	suppr(t_com **list)
{
	t_com *vag;
	t_com *tmp;

	if (list == NULL || *list == NULL)
		return (error(0));
	vag = *list;
	while (vag->c != -1 && vag->u == 0)
		vag = vag->next;
	tmp = vag->prev;
	if (vag->prev && vag->prev->prev)
	{
		vag->prev->prev->next = vag;
		vag->prev = vag->prev->prev;
		free(tmp);
	}
	else if (vag->prev && !vag->prev->prev)
	{
		*list = vag;
		vag->prev = NULL;
		free(tmp);
	}
	return (1);
}

static int	dele(t_com **list)
{
	t_com *vag;
	t_com *tmp;

	if (list == NULL || *list == NULL)
		return (error(0));
	vag = *list;
	while (vag->c != -1 && vag->u == 0)
		vag = vag->next;
	tmp = vag;
	if (vag->c != -1 && vag->prev && vag->next)
	{
		vag->prev->next = vag->next;
		vag->next->prev = vag->prev;
		vag->next->u = 1;
		free(tmp);
	}
	else if (vag->c != -1 && vag->next && !vag->prev)
	{
		*list = vag->next;
		vag->next->u = 1;
		vag->next->prev = NULL;
		free(tmp);
	}
	return (1);
}

int			ft_delete(t_env *env, t_term *b, t_com **list)
{
	if (env == NULL || b == NULL || list == NULL || list == NULL)
		return (error(0));
	if (b->buf[0] == 127)
	{
		suppr(list);
		return (1);
	}
	else if (b->buf[0] == 27 && b->buf[1] == 91 &&
			b->buf[2] == 51 && b->buf[3] == 126)
	{
		dele(list);
		return (1);
	}
	return (-1);
}
