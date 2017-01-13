/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 20:53:15 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 16:07:09 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		count_u(t_com *list)
{
	int	ret;

	if (list == NULL)
		return (error(0));
	ret = 0;
	while (list->u == 0 && list->c != -1)
	{
		ret++;
		list = list->next;
	}
	return (ret);
}

int		get_fork(int i)
{
	static int ret = 0;

	if (i != -1)
		ret = i;
	return (ret);
}

int		delete_t_com(t_com **list)
{
	if (list == NULL || *list == NULL)
		return (error(0));
	while (*list && (*list)->c != -1)
		*list = (*list)->next;
	(*list)->prev = NULL;
	return (1);
}

t_term	*get_buf(t_term *buf)
{
	static t_term	*ret = NULL;

	if (buf != NULL)
		ret = buf;
	return (ret);
}

t_com	**get_begin_list(t_com **list, int o)
{
	static t_com **ret;

	if (o == 1)
		ret = NULL;
	else if (list != NULL)
		ret = list;
	return (ret);
}
