/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:48:53 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 16:35:56 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	is_quote(int c)
{
	if (c == 39 || c == 34)
		return (1);
	else if (c == 96)
		return (3);
	else if (c == 40 || c == 91 || c == 123)
		return (2);
	else
		return (-1);
}

int	fermant(int i, int c)
{
	if ((is_quote(i) == 1 || is_quote(i) == 3) && c == i)
		return (1);
	else if (i == 40 && c == 41)
		return (1);
	else if (i == 91 && c == 93)
		return (1);
	else if (i == 123 && c == 125)
		return (1);
	else
		return (-1);
}

int			count_o(t_com *list)
{
	int ret;

	ret = 0;
	while (list && list->c != -1)
	{
		if (list->c == 13 || list->c == 10)
			ret++;
		list = list->next;
	}
	return (ret);
}

int			ask_for_quote(t_env *v, int quote)
{
	if (v == NULL)
		return (error(0));
	if (quote == 39)
		get_prompt("quote!>");
	else if (quote == 34)
		get_prompt("dquote!>");
	else if (quote == 96)
		get_prompt("bquote!>");
	else if (quote == 40)
		get_prompt("Subsh!>");
	else if (quote == 91)
		get_prompt("Hook!>");
	else if (quote == 123)
		get_prompt("Bracket!>");
	ft_putchar_fd('\n', v->fd);
	affich_prompt(v);
	return (0);
}

int			missing_quote(t_com *list, int ok)
{
	int		letter;
	t_com	*cpy;

	if (list == NULL)
		return (error(0));
	cpy = list;
	while (list && list->c != -1 && (letter = is_quote(list->c)))
	{
		if ((letter == 1 || letter == 3) && (ok = list->c))
			quote_priority(&ok, &list);
		if (list)
			list = list->next;
	}
	if (ok != 1)
		return (ok);
	while (cpy && cpy->c != -1 && (letter = is_quote(cpy->c)))
	{
		if (letter == 1 || letter == 3)
			til_end_of_quote(&cpy);
		if (letter == 2 && (ok = cpy->c))
			check_subsh(&ok, &cpy);
		if (cpy)
			cpy = cpy->next;
	}
	return (ok);
}
