/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 16:37:03 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	print_h(t_histo *h)
{
	int		i;
	int		len;
	int		diff;

	if (h == NULL)
		return (error(0));
	i = 1;
	while (h && h->next && i++)
		h = h->next;
	len = ft_intlen(i) + 1;
	i = 1;
	while (h)
	{
		ft_putnbr_fd(i, get_env(NULL)->fd);
		diff = len - ft_intlen(i);
		if (diff < 0)
			diff = -diff;
		while (diff-- >= 0)
			ft_putchar_fd(' ', get_env(NULL)->fd);
		printlist(h->chaine);
		h = h->prev;
		i++;
	}
	return (0);
}



int		history(t_shell *shell)
{
	t_histo		*histo;

	if (shell == NULL || (histo = get_env(NULL)->histo) == NULL)
		return (1);
	if (count_split(shell->split) < 2)
		return (print_h(histo));
	if (test_h(shell->split) != 0)
		return (m_error(25));
	return (0);
}
