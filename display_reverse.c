/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2017/01/06 16:37:03 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			check_reverse(t_env *v, t_com **l)
{
	t_histo *h;

	if (v == NULL || l == NULL || *l == NULL)
		return (error(0));
	if (get_reverse(-1) == 1)
	{
		h = v->histo;
		while (h && h->next)
			h = h->next;
		while (h && h->prev && h->affich != 1)
			h = h->prev;
		if (h && h->chaine)
		{
			ft_free_l(*l);
			*l = copy_lst(h->chaine);
		}
	}
	get_histo_r(0);
	get_reverse(0);
	reset_affich_histo(v);
	return (1);
}

static int	find_occurence(t_histo *h, t_com *l)
{
	char	*strh;
	char	*strl;

	if (l == NULL || (strl = list2str(l)) == NULL)
		return (0);
	strh = NULL;
	while (h)
	{
		if (h->chaine && (strh = list2str(h->chaine)) != NULL &&
		ft_strstr(strh, strl) != NULL && (h->affich = 1))
			break ;
		if (strh)
		{
			free(strh);
			strh = NULL;
		}
		h = h->next;
	}
	if (strh != NULL)
		free(strh);
	if (strl != NULL)
		free(strl);
	return ((h && h->affich == 1) ? 1 : 0);
}

int			find_in_histo(t_env *v, t_com *l)
{
	t_histo	*h;

	if (v == NULL || l == NULL)
		return (error(0));
	h = v->histo;
	while (h && h->next)
		h = h->next;
	while (h && h->prev && h->affich != 1)
		h = h->prev;
	if (h->affich == 1)
		h = h->next;
	if (!h)
		return (0);
	return (find_occurence(h, l));
}

int			get_reverse(int x)
{
	static int	ret = 0;

	if (x != -1)
		ret = x;
	return (ret);
}

int			display_reverse(t_env *v, t_term *b)
{
	t_histo	*h;

	if (v == NULL || b == NULL)
		return (error(0));
	if (get_histo_r(-1) == 0)
	{
		display(v, b, *get_list(NULL));
		return (1);
	}
	h = v->histo;
	while (h && h->next)
		h = h->next;
	while (h && h->prev && h->affich != 1)
		h = h->prev;
	if ((h && h->affich != 1) || get_reverse(-1) == 0)
	{
		display(v, b, *get_list(NULL));
		return (1);
	}
	if (h && h->chaine)
		display(v, b, h->chaine);
	return (1);
}
