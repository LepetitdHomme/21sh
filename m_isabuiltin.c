/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_isabuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:57 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 18:20:50 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		check_param(t_shell *shell, int i)
{
	if (shell == NULL)
		return (-1);
	if (i == 2)
		if (ft_count(shell->split) != 2 && m_error(10))
			return (0);
	if (i == 3)
		if (ft_count(shell->split) < 2 && m_error(11))
			return (1);
	return (1);
}

int		ft_env_1(t_shell *shell)
{
	if (shell == NULL || shell->environ == NULL)
		return (-1);
	if (check_param(shell, 3) == -1)
		return (-1);
	if (ft_env(shell) == -1)
		return (-1);
	return (1);
}

int		is_a_builtin(t_shell *shell)
{
	if (shell == NULL)
		return (-1);
	if (ft_strcmp(shell->split[0], "cd") == 0)
		return (ft_cd(shell, 0));
	else if (ft_strcmp(shell->split[0], "setenv") == 0)
		return (ft_export(shell));
	else if (ft_strcmp(shell->split[0], "unsetenv") == 0)
		return (ft_unset_env(shell->split, shell, 1));
	else if (ft_strcmp(shell->split[0], "exit") == 0)
		super_exit();
	else if (ft_strcmp(shell->split[0], "env") == 0)
		return (ft_env(shell));
	//else if (ft_strcmp(shell->split[0], "echo") == 0)
	//	return (ft_echo(shell));
	return (0);
}
