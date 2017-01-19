/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 15:29:26 by csellier          #+#    #+#             */
/*   Updated: 2016/12/01 16:28:54 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	error3(int index)
{
	if (index == 20)
		ft_putendl_fd("error: redirection parsing failed", 2);
	else if (index == 19)
		ft_putendl_fd("error: failed to delete redirection", 2);
	return (1);
}

static int	error2(int index)
{
	if (index == 8)
		ft_putendl_fd("error: tgetstr failed", 2);
	else if (index == 9)
		ft_putendl_fd("error: malloc failed", 2);
	else if (index == 10)
		ft_putendl_fd("error: tputs failed", 2);
	else if (index == 11)
		ft_putendl_fd("error: ioctl failed", 2);
	else if (index == 12)
		ft_putendl_fd("error: set_histo failed", 2);
	else if (index == 13)
		ft_putendl_fd("error: copy_list failed", 2);
	else if (index == 14)
		ft_putendl_fd("error: copy_histo failed", 2);
	else if (index == 15)
		ft_putendl_fd("exiting: shell returned error", 2);
	else if (index == 16)
		ft_putendl_fd("error: pipe failed", 2);
	else if (index == 17)
		ft_putendl_fd("error: ambiguous redirection", 2);
	else if (index == 18)
		ft_putendl_fd("error: failed to save redirection", 2);
	else
		error3(index);
	return (1);
}

int			error(int index)
{
	if (index == 0)
		ft_putendl_fd("error: transmission failed", 2);
	else if (index == 1)
		ft_putendl_fd("error: env seems empty", 2);
	else if (index == 2)
		ft_putendl_fd("error: env opy failed", 2);
	else if (index == 3)
		ft_putendl_fd("error: open fd failed", 2);
	else if (index == 4)
		ft_putendl_fd("error: getenv failed", 2);
	else if (index == 5)
		ft_putendl_fd("error: tcgetattr failed", 2);
	else if (index == 6)
		ft_putendl_fd("error: tcsetattr failed", 2);
	else if (index == 7)
		ft_putendl_fd("error: set_buf failed", 2);
	else
		error2(index);
	if (index > 6)
		super_exit();
	ft_putendl_fd("exiting process", 2);
	exit(EXIT_SUCCESS);
	return (-1);
}

void		super_exit(void)
{
	set_terme(&get_env(NULL)->term);
	tputs(tgetstr("ve", NULL), 0, ft_out);
	exit(EXIT_SUCCESS);
}
