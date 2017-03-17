/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:31:40 by csellier          #+#    #+#             */
/*   Updated: 2017/03/15 18:05:58 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_com	*back_in_h(int i)
{
	t_histo	*histo;

	if ((histo = get_env(NULL)->histo) == NULL && m_error(26))
		return (NULL);
	while (++i < 0)
	{
		if (!histo->next && m_error(26))
			return (NULL);
		histo = histo->next;
		i++;
	}
	ft_putendl_fd(list2str(histo->chaine), 2);
	return (histo->chaine);
}

static t_com	*h_by_nmb(int i)
{
	t_histo *h;
	int		j;

	if ((h = get_env(NULL)->histo) == NULL && m_error(26))
		return (NULL);
	while (h && h->next)
		h = h->next;
	j = 1;
	while (h && h->prev)
	{
		if (j == i)
			break ;
		h = h->prev;
		j++;
	}
	if (i != j && m_error(26))
		return (NULL);
	ft_putendl_fd(list2str(h->chaine), 2);
	return (h->chaine);
}

t_com			*bang(char *com, int i)
{
	int	hline;
	int	len;

	if (i + 1 >= (len = (int)ft_strlen(com)))
		return (NULL);
	if ((hline = ft_atoi(&com[i + 1])) < 0)
		return (back_in_h(hline));
	else if (hline > 0)
		return (h_by_nmb(hline));
	return (NULL);
}	
