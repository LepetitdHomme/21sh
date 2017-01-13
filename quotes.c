/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:34:46 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:30:38 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			suppr_quote(t_com **list, t_com *quote)
{
	if (list == NULL || *list == NULL || quote == NULL)
		return (error(0));
	if (quote->prev)
	{
		quote->prev->next = quote->next;
		quote->next->prev = quote->prev;
	}
	else
	{
		*list = quote->next;
		quote->next->prev = *list;
	}
	free(quote);
	return (1);
}

int			parse_quote(t_env *v, t_com **list, int first)
{
	t_com	*vag;

	if (v == NULL || list == NULL || *list == NULL)
		return (error(0));
	vag = *list;
	while (vag && vag->c != -1)
	{
		if (is_quote(vag->c) == 1 && first == 0)
		{
			first = vag->c;
			vag = vag->next;
			suppr_quote(list, vag->prev);
			while (vag && vag->c != first)
				vag = vag->next;
			first = 0;
			if (vag)
			{
				vag = vag->next;
				suppr_quote(list, vag->prev);
			}
		}
		else
			vag = vag->next;
	}
	return (1);
}

static int	insert_carriot_return(t_env *v)
{
	t_com	*vag;
	t_com	*new;

	if (v == NULL)
		return (error(0));
	vag = v->begin;
	while (vag && vag->c != -1)
		vag = vag->next;
	if ((new = (t_com *)malloc(sizeof(t_com))) == NULL)
		return (error(9));
	new->u = 0;
	new->h = 0;
	new->c = 10;
	new->next = vag;
	if (vag->prev)
	{
		new->prev = vag->prev;
		vag->prev->next = new;
		vag->prev = new;
		return (1);
	}
	new->prev = NULL;
	v->begin = new;
	vag->prev = new;
	return (1);
}

int			quotes(t_env *v, t_term *b, t_com **list)
{
	int				quote;

	if (v == NULL || b == NULL || list == NULL || *list == NULL)
		return (error(0));
	if (concat_lst(v, *list) == -1)
		return (-1);
	quote = missing_quote(v->begin, 1);
	if (quote != 1)
	{
		v->missin_q = 1;
		insert_carriot_return(v);
		get_env(v);
		ask_for_quote(v, quote);
		return (-2);
	}
	ft_free_l(*list);
	*list = NULL;
	if ((*list = copy_lst(v->begin)) == NULL)
		return (error(13));
	ft_free_l(v->begin);
	v->begin = NULL;
	get_env(v);
	v->missin_q = 0;
	get_prompt("MonTerm>");
	return (1);
}
