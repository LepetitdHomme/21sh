/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:53:58 by csellier          #+#    #+#             */
/*   Updated: 2016/12/01 17:19:33 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	set_env(t_env *env, int argc, char **argv, char **v)
{
	if (env == NULL || argv == NULL || v == NULL)
		return (error(0));
	env->argc = argc;
	env->argv = argv;
	if ((env->env = copy_split(v)) == NULL)
		return (error(2));
	if ((env->fd = open("/dev/tty", O_RDWR)) < 0)
		return (error(3));
	get_prompt("MonTerm>");
	env->begin = NULL;
	env->histo = NULL;
	env->c_histo = NULL;
	env->missin_q = 0;
	return (1);
}

int	set_histo(t_env *env, t_com *l)
{
	t_histo	*h;

	if (env == NULL || l == NULL)
		return (error(0));
	if (env->histo == NULL)
	{
		if ((h = (t_histo *)malloc(sizeof(t_histo))) == NULL)
			return (error(9));
		h->next = NULL;
		h->prev = NULL;
		copy_list(h, l);
		h->affich = 0;
		env->histo = h;
		return (1);
	}
	return (1);
}

int	set_terme(struct termios *term)
{
	if (term == NULL)
		return (-1);
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (error(6));
	return (1);
}

int	set_list(t_com **list)
{
	if (*list != NULL)
	{
		ft_free_l(*list);
		*list = NULL;
	}
	if ((*list = (t_com *)malloc(sizeof(t_com))) == NULL)
		return (error(9));
	(*list)->u = 1;
	(*list)->h = 0;
	(*list)->prev = NULL;
	(*list)->next = NULL;
	(*list)->c = -1;
	return (1);
}

int	set_buf(t_term *buf)
{
	struct winsize	w;

	if (buf == NULL)
		return (error(0));
	if ((buf->cd = tgetstr("cd", NULL)) == NULL ||
	(buf->le = tgetstr("le", NULL)) == NULL ||
	(buf->nd = tgetstr("nd", NULL)) == NULL ||
	(buf->cr = tgetstr("cr", NULL)) == NULL ||
	(buf->up = tgetstr("up", NULL)) == NULL ||
	(buf->me = tgetstr("me", NULL)) == NULL ||
	(buf->ho = tgoto(tgetstr("ch", NULL), 0, 0)) == NULL ||
	(buf->mr = tgetstr("mr", NULL)) == NULL ||
	(buf->ve = tgetstr("ve", NULL)) == NULL ||
	(buf->vi = tgetstr("vi", NULL)) == NULL)
		return (error(8));
	if ((buf->cl = tgetstr("cl", NULL)) == NULL ||
	(ioctl(0, TIOCGWINSZ, &w) == -1))
		return (error(11));
	buf->w_col = w.ws_col;
	buf->w_row = w.ws_row;
	buf->count_cr = 0;
	buf->pp = NULL;
	ft_bzero(buf->buf, 8);
	get_buf(buf);
	return (1);
}
