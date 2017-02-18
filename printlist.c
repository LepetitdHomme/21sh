/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 16:37:03 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		test_h(char **split)
{
	if (split == NULL)
		return (error(0));
	if (count_split(split) < 2)
		return (1);
	if (ft_strcmp(split[1], "-c") != 0 && ft_strcmp(split[1], "-d") != 0 &&
	ft_strcmp(split[1], "-p") != 0 && ft_strcmp(split[1], "-s") != 0)
		return (1);
	return (0);
}

int		printlist(t_com *list)
{
	if (list == NULL)
		return (1);
	while (list && list->c != -1)
	{
		ft_putchar_fd(list->c, get_env(NULL)->fd);
		list = list->next;
	}
	ft_putchar_fd('\n', get_env(NULL)->fd);
	return (0);
}
