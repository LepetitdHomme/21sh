/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 15:29:26 by csellier          #+#    #+#             */
/*   Updated: 2016/12/01 16:28:54 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	just_do_it(t_shell *shell, int x)
{
	int	i;

	if (shell == NULL || shell->split == NULL || x == 0)
		return (error(0));
	i = 1;
	while (shell->split && shell->split[i])
	{
		ft_putstr_fd(shell->split[i], get_env(NULL)->fd);
		if (i + 1 >= x - 1)
			break ;
		ft_putchar_fd(' ', get_env(NULL)->fd);
		i++;
	}
	ft_putchar_fd('\n', get_env(NULL)->fd);
	return (1);
}

int			ft_echo(t_shell *shell)
{
	int	x;
	int	i;

	if (shell == NULL)
		return (error(0));
	if (shell->split == NULL || (x = count_split(shell->split)) == 0)
		return (1);
	if (x < 2 && ft_putendl_fd("", get_env(NULL)->fd))
		return (0);
	if (ft_strncmp(shell->split[1], "-n", 2) == 0)
	{
		if (x < 3)
			return (0);
		i = 1;
		while (shell->split && shell->split[++i])
		{
			ft_putstr_fd(shell->split[i], get_env(NULL)->fd);
			if (i + 1 >= x - 1)
				break ;
			ft_putchar_fd(' ', get_env(NULL)->fd);
		}
	}
	else
		just_do_it(shell, x);
	return (0);
}
