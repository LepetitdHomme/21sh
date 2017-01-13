/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:39:03 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:43:51 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_sigwinch(int s)
{
	t_term	*buf;

	(void)s;
	if ((buf = get_buf(NULL)) == NULL)
		return ;
	tputs(buf->cl, 0, ft_out);
	affich_prompt(get_env(NULL));
	set_buf(buf);
	signal(SIGINT, SIG_IGN);
	display(get_env(NULL), buf, *get_list(NULL));
	signal(SIGINT, ft_signal);
}

void	ft_all_sig(void)
{
	int i;

	i = 0;
	while (i < 31)
	{
		if (i == SIGWINCH)
			signal(i, ft_sigwinch);
		else if (i == SIGINT || i == SIGTSTP)
			signal(i, SIG_IGN);
		i++;
	}
}
