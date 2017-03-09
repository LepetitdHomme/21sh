/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 14:07:36 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:51:53 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_com	**get_list(t_com **list)
{
	static t_com	**ret;

	if (list != NULL)
		ret = list;
	return (ret);
}

void	ft_signal_3(int echo)
{
	(void)echo;
	return ;
}

void	ft_signal_2(int echo)
{
	(void)echo;
	ft_putendl_fd("", get_fd(-1));
}

void	ft_signal(int echo)
{
	t_env	*cp;
	t_com	**list;

	(void)echo;
	cp = get_env(NULL);
	list = get_list(NULL);
	get_prompt("MonTerm>");
	if (cp->begin != NULL)
		ft_free_l(cp->begin);
	get_env(NULL)->begin = NULL;
	get_env(NULL)->missin_q = 0;
	get_histo_r(0);
	get_reverse(0);
	reset_affich_histo(get_env(NULL));
	if (cp->c_histo == NULL)
		set_list(list);
	else
		suppr_list(cp, list);
	ft_putendl_fd("", cp->fd);
	affich_prompt(cp);
}

int		suppr_list(t_env *cp, t_com **list)
{
	t_histo	*h;

	if (cp == NULL || list == NULL || *list == NULL)
		return (0);
	h = cp->c_histo;
	if (h->affich != 1)
	{
		while (h && h->affich != 1)
			h = h->next;
		mini_clear(h->chaine);
		h->affich = 0;
		cp->c_histo->affich = 1;
	}
	else
		set_list(list);
	return (1);
}
