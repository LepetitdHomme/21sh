/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:03:18 by csellier          #+#    #+#             */
/*   Updated: 2016/11/28 18:46:57 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		get_term_size(t_env *env)
{
	if (env == NULL)
		return (error(0));
	return (ft_strlen(get_prompt(NULL)));
}

int		count_histo(t_histo *list)
{
	int		ret;

	if (list == NULL)
		return (error(0));
	ret = 0;
	while (list)
	{
		list = list->next;
		ret++;
	}
	return (ret);
}

int		get_fd(int file)
{
	static int	fd;

	if (file != -1)
		fd = file;
	return (fd);
}

t_com	*new_com(t_com *cp)
{
	t_com	*new;

	if (cp == NULL && error(0))
		return (NULL);
	if ((new = (t_com *)malloc(sizeof(t_com))) == NULL && error(9))
		return (NULL);
	new->c = cp->c;
	new->u = 0;
	new->h = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_env	*get_env(t_env *v)
{
	static t_env	*env = NULL;

	if (v != NULL)
		env = v;
	return (env);
}
