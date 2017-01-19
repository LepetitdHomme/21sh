/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:34:36 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:51:55 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** The 'boucle' function, reads each input and sends it to 'treat',
** updates historic if needed and displays the result
*/

static int	stop(t_term *buf, t_com *list)
{
	if (buf == NULL)
		return (error(0));
	if (list != NULL)
	{
		if (buf->buf[0] == 4 && list->c == -1)
		{
			ft_free_l(list);
			return (1);
		}
	}
	return (-1);
}

static int	boucle(t_env *env, t_term *buf)
{
	static int	first = 0;
	t_com		*list;

	if (env == NULL || buf == NULL)
		return (error(0));
	list = NULL;
	if (set_list(&list) == -1 || affich_prompt(env) == -1)
		return (error(7));
	get_list(&list);
	ft_bzero(buf->buf, 8);
	signal(SIGINT, ft_signal);
	get_stdin(STDIN_FILENO);
	while (read(0, buf->buf, 8) != 0 && stop(buf, *get_list(NULL)) != 1)
	{
		signal(SIGINT, SIG_IGN);
		if (treat(env, buf, get_list(NULL)) == 42 && copy_histo(env))
			if (c_histo_b(env) && first == 0 && (first = 1))
				ft_free_l(list);
		ft_bzero(buf->buf, 8);
		if (env->c_histo != NULL)
			get_list(&which_list(env)->chaine);
		display_reverse(env, buf);
		signal(SIGINT, ft_signal);
	}
	return (1);
}

int			mode_canonique(struct termios term_o)
{
	struct termios term;

	term = term_o;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	set_terme(&term);
	return (1);
}

int			main(int argc, char **argv, char **env)
{
	t_env			v;
	t_term			buf;
	char			*name_t;
	struct termios	term_restor;

	if (argv == NULL || env == NULL || count_split(env) == 0)
		return (error(1));
	if ((name_t = getenv("TERM")) == NULL)
		return (error(4));
	if (tgetent(NULL, name_t) <= 0)
		return (error(4));
	if (tcgetattr(0, &term_restor) == -1)
		return (error(5));
	set_env(&v, argc, argv, env);
	v.term = term_restor;
	get_env(&v);
	get_fd(v.fd);
	mode_canonique(term_restor);
	if (set_buf(&buf) == -1)
		return (error(7));
	ft_all_sig();
	boucle(&v, &buf);
	free_main(v);
	super_exit();
	return (0);
}
