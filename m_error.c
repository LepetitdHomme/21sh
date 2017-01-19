/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:42 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 19:28:06 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		error123(int i)
{
	if (i == 20)
		ft_putendl_fd("error: syntax mistake near unexpected operande", 2);
	else if (i == 21)
		ft_putendl_fd("warning: pipeheredoc not handled", 2);
	else if (i == 22)
		ft_putendl_fd("warning: environment variable HOME seems undefined", 2);
	else if (i == 23)
		ft_putendl_fd("error: ambiguous flag detected", 2);
	else if (i == 24)
		ft_putendl_fd("warning: current directory not found, PWD set physically"
		, 2);
	return (1);
}

int		error1_10(int i)
{
	if (i == 11 && ft_putendl_fd("warning : no option handled", 2))
		ft_putendl_fd("", 2);
	if (i == 12)
		ft_putendl_fd("error : impossible redirection", 2);
	if (i == 13)
		ft_putendl_fd("error : permission denied", 2);
	if (i == 14)
		ft_putendl_fd("error : flag not handled", 2);
	if (i == 15)
		ft_putendl_fd("error : need [fd>file], [fd>&fd], or [>..] form", 2);
	if (i == 16)
		ft_putendl_fd("error : fd : unknown or bad file descriptor", 2);
	if (i == 17)
		ft_putendl_fd("error : redirection treatment failed", 2);
	if (i == 18)
		ft_putendl_fd("error : no command found", 2);
	if (i == 19)
		ft_putendl_fd("error : redirection not implemented", 2);
	else
		error123(i);
	return (1);
}

int		m_error(int i)
{
	ft_putstr_fd(ROUGE, 2);
	if (i == 0)
		ft_putendl_fd("error when initializing structure", 2);
	if (i == 1)
		ft_putendl_fd("error when splitting command", 2);
	if (i == 2)
		ft_putendl_fd("error : wrong command", 2);
	if (i == 3)
		ft_putendl_fd("error while freeing command split", 2);
	if (i == 4)
		ft_putendl_fd("error : no prompt to display", 2);
	if (i == 5)
		ft_putstr_fd("error : command not found : ", 2);
	if (i == 6)
		ft_putendl_fd("error : malloc failure", 2);
	if (i == 7 && ft_putendl_fd("error : need argument", 2))
		ft_putendl_fd("usage : [-u] name", 2);
	if (i == 8 && ft_putendl_fd("error unsetenv : no such variable", 2))
		ft_putendl_fd("usage : unsetenv name", 2);
	if (i == 10)
		ft_putendl_fd("error : need NAME=VALUE form", 2);
	if (i > 10)
		error1_10(i);
	ft_putstr_fd(END, 2);
	return (1);
}
