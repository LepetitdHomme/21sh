/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affich.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:22:09 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_out(int c)
{
	ft_putchar_fd(c, get_fd(-1));
	return (1);
}

static int	set_cursor(t_env *env, t_term *buf)
{
	size_t	d;
	int		e;

	if (env == NULL || buf == NULL)
		error(0);
	d = 0;
	e = 0;
	while (e++ < buf->count_cr)
		tputs(buf->up, 0, ft_out);
	tputs(buf->ho, 0, ft_out);
	while (d++ < ft_strlen(get_prompt(NULL)))
		tputs(buf->nd, 0, ft_out);
	tputs(buf->cd, 0, ft_out);
	buf->count_cr = 0;
	return (1);
}

int			display(t_env *env, t_term *buf, t_com *list)
{
	t_com	*init;
	int		c;

	if (env == NULL || buf == NULL || list == NULL || !(init = list))
		return (error(0));
	c = get_term_size(env);
	set_cursor(env, buf);
	while (list && list->c != -1)
	{
		if (c + 1 > buf->w_col && (buf->count_cr += 1))
		{
			c = 0;
			ft_putchar_fd('\n', env->fd);
		}
		affich_curs(list, init, buf, 0);
		c++;
		if (list && (list->c == 13 || list->c == 10) && (buf->count_cr += 1))
			c = 0;
		if (list && list->c != -1)
			ft_putchar_fd(list->c, env->fd);
		affich_curs(list, init, buf, 1);
		list = list->next;
	}
	affich_curs(list, init, buf, 1);
	return (1);
}

int			affich_curs(t_com *cour, t_com *list, t_term *buf, int i)
{
	t_com	*vag;

	if (cour == NULL || list == NULL || buf == NULL)
		return (error(0));
	vag = list;
	while (vag->next)
		vag = vag->next;
	if (vag->u == 1)
		tputs(buf->ve, 0, ft_out);
	if (vag->u == 0)
		tputs(buf->vi, 0, ft_out);
	if (i == 0 && (cour->u == 1 || cour->h == 1))
	{
		if (cour->u == 1)
			ft_putstr_fd(CYAN, get_fd(-1));
		tputs(buf->mr, 0, ft_out);
	}
	else if (i == 1 && (cour->u == 1 || cour->h == 1))
	{
		tputs(buf->me, 0, ft_out);
		if (cour->u == 1)
			ft_putstr_fd(END, get_fd(-1));
	}
	return (1);
}

int			affich_prompt(t_env *env)
{
	if (env == NULL)
		return (error(0));
	ft_putstr_fd(GREEN, env->fd);
	ft_putstr_fd(get_prompt(NULL), env->fd);
	ft_putstr_fd(END, env->fd);
	return (1);
}
