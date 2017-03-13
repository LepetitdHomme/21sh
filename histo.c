/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csllier@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:00:44 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:23:06 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			save_line(t_env *env, t_com *l)
{
	t_histo	*new;
	t_histo	*vag;

	if (env == NULL || l == NULL)
		return (error(0));
	if (env->histo == NULL)
		return (set_histo(env, l));
	if ((new = (t_histo *)malloc(sizeof(t_histo))) == NULL)
		return (error(9));
	vag = env->histo;
	while (vag->next)
		vag = vag->next;
	if (count_histo(env->histo) >= 30)
	{
		vag->prev->next = NULL;
		ft_free_l(vag->chaine);
		free(vag);
	}
	copy_list(new, l);
	new->next = env->histo;
	new->prev = NULL;
	env->histo->prev = new;
	env->histo = new;
	env->histo->affich = 0;
	return (1);
}

t_histo		*which_list(t_env *env)
{
	t_histo		*vag;

	if (env == NULL || env->c_histo == NULL)
	{
		error(0);
		return (NULL);
	}
	vag = env->c_histo;
	while (vag)
	{
		if (vag->affich == 1)
		{
			if (vag->chaine == NULL)
			{
				error(0);
				return (NULL);
			}
			return (vag);
		}
		vag = vag->next;
	}
	return (NULL);
}

int			c_histo_b(t_env *env)
{
	t_histo	*vag;
	t_histo	*new;

	if (env == NULL)
		return (error(0));
	vag = env->c_histo;
	if ((new = (t_histo *)malloc(sizeof(t_histo))) == NULL)
		return (error(9));
	new->prev = NULL;
	new->next = vag;
	env->c_histo->prev = new;
	new->chaine = newcom();
	new->affich = 1;
	env->c_histo = new;
	return (1);
}

int			copy_histo(t_env *env)
{
	t_histo		*copy;
	t_histo		*histo;

	if (env == NULL || (copy = (t_histo *)malloc(sizeof(t_histo))) == NULL)
		return (error(14));
	histo = env->histo;
	copy_list(copy, env->histo->chaine);
	copy->affich = env->histo->affich;
	refresh_histo(env, copy);
	env->c_histo->next = NULL;
	env->c_histo->prev = NULL;
	histo = histo->next;
	while (histo)
	{
		if ((copy->next = (t_histo *)malloc(sizeof(t_histo))) == NULL)
			return (error(14));
		copy_list(copy->next, histo->chaine);
		copy->next->affich = histo->affich;
		copy->next->prev = copy;
		histo = histo->next;
		copy = copy->next;
	}
	copy->next = NULL;
	return (1);
}

int			copy_list(t_histo *a, t_com *b)
{
	t_com	*c;

	if (b == NULL || a == NULL || (c = (t_com *)malloc(sizeof(t_com))) == NULL)
		return (error(13));
	c->c = b->c;
	c->u = b->u;
	c->h = b->h;
	c->prev = NULL;
	c->next = NULL;
	a->chaine = c;
	b = b->next;
	while (b)
	{
		if ((c->next = (t_com *)malloc(sizeof(t_com))) == NULL)
			return (error(13));
		c->next->c = b->c;
		c->next->u = b->u;
		c->next->h = b->h;
		c->next->prev = c;
		b = b->next;
		c = c->next;
	}
	c->next = NULL;
	return (1);
}
