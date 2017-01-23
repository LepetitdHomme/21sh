/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:26 by csellier          #+#    #+#             */
/*   Updated: 2016/11/23 13:59:48 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_21sh.h"

int		exit_status(int c)
{
	int	status;
	if (!WIFEXITED(c) && ret_fils(c))
		return (1);
	status = (WEXITSTATUS(c) == 0) ? 0 : 1;
	get_status(status);
	return (1);
}

int		get_status(int x)
{
	static int	status = 0;

	if (x != -2)
		status = x;
	return (status);
}

int		which_operand(char c)
{
	if (c == ';')
		return (1);
	else if (c == '&')
		return (2);
	else if (c == '|')
		return (3);
	else if (c == '>' || c == '<')
		return (4);
	return (0);
}
