/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:20:39 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			history_cflag(void)
{
	t_env	*env;

	if ((env = get_env(NULL)) == NULL)
		return (1);
	if (env->histo == NULL)
		return (0);
	ft_free_h(env->histo);
	env->histo = NULL;
	return (0);
}

static int	delete_this(t_histo *h)
{
	t_env	*env;

	if (h == NULL || (env = get_env(NULL)) == NULL)
		return (1);
	if (!h->prev)
	{
		env->histo = h->next;
		if (h->next)
			h->next->prev = NULL;
	}
	else
	{
		h->prev->next = h->next;
		if (h->next)
			h->next->prev = h->prev;
	}
	ft_free_l(h->chaine);
	free(h);
	return (0);
}

int			history_dflag(char *offset)
{
	t_env	*v;
	t_histo	*h;
	int		ofset;
	int		i;

	if (offset == NULL || (v = get_env(NULL)) == NULL)
		return (1);
	if ((h = v->histo) == NULL)
		return (1);
	ofset = ft_atoi(offset);
	i = 1;
	while (h)
	{
		if (i == ofset)
		{
			delete_this(h);
			break ;
		}
		h = h->next;
		i++;
	}
	return ((i == ofset) ? 0 : m_error(26));
}
