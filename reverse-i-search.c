/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse-i-search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2017/01/06 16:37:03 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				read_histo(t_env *v, t_term *b, t_com **l)
{
	if (v == NULL || b == NULL || l == NULL || *l == NULL)
		return (error(0));
	if (v->histo == NULL)
		return (0);
	if (find_in_histo(v, *l) == 0)
		return (0);
	return (1);
}

int				get_histo_r(int x)
{
	static int	ret = 0;

	if (x != -1)
		ret = x;
	return (ret);
}

int			set_prompt_for_reverse(t_env *v, t_term *b, int i)
{
	int		e;

	if (v == NULL || b == NULL)
		return (error(0));
	e = 0;
	if (get_histo_r(-1) == 1)
	{
		while (e++ < b->count_cr)
			tputs(b->up, 0, ft_out);
		tputs(b->ho, 0, ft_out);
		tputs(b->cd, 0, ft_out);
		b->count_cr = 0;
	}
	if (i == 2)
		get_prompt("(reverse-i-search)failed for>");
	else if (i == 1)
		get_prompt("(reverse-i-search)>");
	else
		get_prompt("MonTerm>");
	if(get_histo_r(-1) == 1)
		affich_prompt(v);
	return (1);
}

int			reset_affich_histo(t_env *v)
{
	t_histo *h;

	if (v == NULL)
		return (error(0));
	h = v->histo;
	while (h)
	{
		h->affich = 0;
		h = h->next;
	}
	return (1);
}

int			ctrlr(t_env *v, t_term *b, t_com **l, int i)
{
	if (v == NULL || b == NULL || l == NULL || *l == NULL)
		return (error(0));
	if (b->buf[0] == 10 || (*l)->c == -1)
		return (0);
	if (i == 1 && b->buf[0] != 18)
	{
		get_reverse(0);
		set_prompt_for_reverse(v, b, 0);
		get_histo_r(0);
		reset_affich_histo(v);
		return (0);
	}
	get_histo_r(1);
	if (i == 0)
		reset_affich_histo(v);
	if (read_histo(v, b, l) == 1)
	{
		set_prompt_for_reverse(v, b, 1);
		get_reverse(1);
	}
	else
	{
		set_prompt_for_reverse(v, b, 2);
		get_reverse(0);
	}
	return (1);
}
