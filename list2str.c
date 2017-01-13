/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 20:00:10 by csellier          #+#    #+#             */
/*   Updated: 2016/11/28 11:03:34 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*list2str_tabu(t_com *list)
{
	char	*ret;
	int		count;
	t_com	*vag;
	int		i;

	if (list == NULL)
		return (NULL);
	vag = list;
	count = 0;
	i = 0;
	while (vag && vag->c != -1 && vag->u != 1)
	{
		vag = vag->next;
		count++;
	}
	if ((ret = (char *)malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	ret[count] = '\0';
	while (i < count)
	{
		ret[i] = list->c;
		list = list->next;
		i++;
	}
	return (ret);
}

char	*list2str(t_com *list)
{
	char	*ret;
	int		count;
	t_com	*vag;
	int		i;

	if (list == NULL)
		return (NULL);
	vag = list;
	count = 0;
	i = 0;
	while (vag && vag->c != -1)
	{
		vag = vag->next;
		count++;
	}
	if ((ret = (char *)malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	ret[count] = '\0';
	while (i < count)
	{
		ret[i] = list->c;
		list = list->next;
		i++;
	}
	return (ret);
}
