/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operande.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 16:37:03 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ope(char c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<')
		return (1);
	return (-1);
}

int		is_operande(char *list, int i)
{
	if (list == NULL)
		return (-1);
	if (i - 1 >= 0 && ope(list[i - 1]) == 1)
		return (-1);
	if (i + 1 < (int)ft_strlen(list) && ope(list[i + 1]) == 1)
		return (-1);
	return (1);
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
