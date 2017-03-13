/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tool2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 18:07:24 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	print_h_p2(t_histo *h, int arg, int arg2, t_com *l)
{
	int	len;
	int	diff;
	int	i;

	if (h == NULL || l == NULL)
		return (1);
	len = count_histo(h) + 1;
	i = 1;
	while (h)
	{
		ft_putnbr_fd(i, get_env(NULL)->fd);
		diff = len - ft_intlen(i);
		if (diff < 0)
			diff = -diff;
		while (diff-- >= 0)
			ft_putchar_fd(' ', get_env(NULL)->fd);
		if ((i == arg || i == arg2) && (printlist(l) == 0))
			l = h->chaine;
		else
			printlist(h->chaine);
		h = h->prev;
		i++;
	}
	return (0);
}

static int	print_h_p(t_histo *h, int arg, int arg2)
{
	int		i;
	t_com	*l;

	if (h == NULL)
		return (1);
	l = NULL;
	i = count_histo(h);
	while (h && h->next)
	{
		if (i == arg2)
			l = h->chaine;
		h = h->next;
		i--;
	}
	return (print_h_p2(h, arg, arg2, l));
}

int			history_pflag(char **split, t_histo *h)
{
	int		arg;
	int		arg2;
	int		len;

	if ((split == NULL || count_split(split) < 4 || h == NULL) && m_error(25))
		return (1);
	if ((arg = ft_atoi(split[2])) == 0 && m_error(25))
		return (1);
	if ((arg2 = ft_atoi(split[3])) == 0 && m_error(25))
		return (1);
	len = count_histo(h);
	if ((arg > len || arg2 > len) && m_error(25))
		return (1);
	return (print_h_p(h, arg, arg2));
}
