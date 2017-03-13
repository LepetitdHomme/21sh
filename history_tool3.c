/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tool3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:36:02 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_com	*end_it(t_com *ret)
{
	if (ret == NULL)
		return (NULL);
	if ((ret->next = (t_com *)malloc(sizeof(t_com))) == NULL)
		return (NULL);
	ret->next->c = -1;
	ret->next->h = 0;
	ret->next->u = 1;
	ret->next->prev = ret;
	ret->next->next = NULL;
	while (ret->prev)
	{
		ret->prev->next = ret;
		ret = ret->prev;
	}
	return (ret);
}

static int		put_space(t_com *ret, t_com **prev)
{
	if (ret == NULL)
		return (1);
	*prev = malloc(sizeof(t_com));
	(*prev)->c = 32;
	(*prev)->u = 0;
	(*prev)->h = 0;
	(*prev)->prev = ret;
	(*prev)->next = NULL;
	return (1);
}

t_com			*str2list(char **split)
{
	t_com	*ret;
	t_com	*prev;
	int		i;
	int		j;

	if (split == NULL)
		return (NULL);
	i = -1;
	prev = NULL;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			ret = (t_com *)malloc(sizeof(t_com));
			ret->c = split[i][j];
			ret->u = 0;
			ret->h = 0;
			ret->prev = prev;
			ret->next = NULL;
			prev = ret;
		}
		(size_t)(i + 1) < count_split(split) ? put_space(ret, &prev) : 0;
	}
	return (end_it(ret));
}

int				history_sflag(char **split, t_histo *h)
{
	t_com	*ret;

	if (split == NULL || h == NULL)
		return (1);
	if (count_split(split) < 3)
		return (1);
	ret = str2list(&split[2]);
	while (ret->prev)
		ret = ret->prev;
	save_line(get_env(NULL), ret);
	ft_free_l(ret);
	return (1);
}
