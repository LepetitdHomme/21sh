/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 16:01:51 by csellier          #+#    #+#             */
/*   Updated: 2016/12/01 21:48:08 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	quote_priority(int *ok, t_com **list)
{
	if (ok == NULL || list == NULL || *list == NULL)
		error(0);
	*ok = (*list)->c;
	*list = (*list)->next;
	while (*list && (*list)->c != -1)
	{
		if (fermant(*ok, (*list)->c) == 1)
		{
			*ok = 1;
			break ;
		}
		*list = (*list)->next;
	}
}

int		end_of_quote(char *list, int i)
{
	int	c;
	int	pb;

	if (list == NULL || i < 0)
		return (error(0));
	if (is_quote(list[i]) == -1)
		return (error(0));
	pb = i;
	c = list[i];
	i++;
	while (list && list[i])
	{
		if (fermant(c, list[i]) == 1)
			return (i);
		i++;
	}
	return (pb);
}

int		til_end_of_quote(t_com **list)
{
	int	useless;

	if (list == NULL || *list == NULL)
		return (error(0));
	useless = 1;
	quote_priority(&useless, list);
	return (1);
}

int		check_subsh(int *ok, t_com **list)
{
	int	letter;

	if (ok == NULL || list == NULL || *list == NULL)
		return (error(0));
	*ok = (*list)->c;
	*list = (*list)->next;
	letter = 0;
	while (*list && (*list)->c != -1)
	{
		letter = is_quote((*list)->c);
		if (letter == 1 || letter == 3)
			til_end_of_quote(list);
		if (fermant(*ok, (*list)->c) == 1)
		{
			*ok = 1;
			break ;
		}
		*list = (*list)->next;
	}
	return (1);
}
