/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 14:00:09 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 14:35:07 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		get_stdin(int fd)
{
	static int	fdstdin;

	if (fd != -1)
		fdstdin = dup(fd);
	return (fdstdin);
}

int		get_piperead(int fd)
{
	static int	piperead = -2;

	if (fd != -1)
		piperead = fd;
	return (piperead);
}

int		index_pwd(char **env, char *cmp)
{
	int i;

	if (env == NULL || cmp == NULL)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], cmp, ft_strlen(cmp)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_coller_tool(t_com **vag, t_com **tmp, t_com **list)
{
	if (vag == NULL || *vag == NULL || *tmp == NULL || list == NULL)
		return (error(0));
	if ((*vag)->prev)
		(*vag) = (*vag)->prev;
	else if (!(*vag)->prev && *tmp)
	{
		(*vag)->prev = new_com(*tmp);
		*tmp = (*tmp)->next;
		*vag = (*vag)->prev;
		*list = *vag;
	}
	return (1);
}

t_com	*newcom(void)
{
	t_com	*new;

	if ((new = (t_com *)malloc(sizeof(t_com))) == NULL && error(9))
		return (NULL);
	new->c = -1;
	new->u = 1;
	new->h = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
