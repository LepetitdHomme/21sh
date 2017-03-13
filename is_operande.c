/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operande.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:22:04 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:22:08 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ope(char c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<')
		return (1);
	return (-1);
}

int		redir_is_first(char *list)
{
	int i;

	if (list == NULL)
		return (error(0));
	i = 0;
	while (list && list[i] == ' ')
		i++;
	if (list[i] && is_redir(list[i]) == 1)
		return (1);
	return (-1);
}
