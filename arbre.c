/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbre.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:10:20 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 18:21:23 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			my_fork(t_shell *shell, t_bin *bin)
{
	pid_t	j;
	int		pipefd[2];

	if (shell == NULL || bin == NULL)
		return (error(0));
	if (pipe(pipefd) != 0)
		return (error(16));
	j = fork();
	if (j == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		lecture(shell, bin->left);
		exit(EXIT_SUCCESS);
	}
	else if (j > 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		lecture(shell, bin->right);
		wait(&j);
	}
	return (1);
}

int			get_static_fork(int i)
{
	static int f = 0;

	if (i != -1)
		f = i;
	return (f);
}

static int	bintype2(int j, t_shell *shell, t_bin *bin)
{
	pid_t	i;

	if (shell == NULL || bin == NULL)
		return (1);
	if (j != 0 && my_fork(shell, bin))
		return (1);
	get_static_fork(1);
	i = fork();
	if (i == 0)
		my_fork(shell, bin);
	else if (i > 0)
	{
		wait(&i);
		exit_status(i);
	}
	return (1);
}

int			lecture(t_shell *shell, t_bin *bin)
{
	int			j;

	if (shell == NULL || bin == NULL)
		return (1);
	j = get_static_fork(-1);
	if (bin->type == 0)
		if (check_builtin(shell, bin->sub, 0) == -1)
			return (error(15));
	if (bin->type == 1 && lecture(shell, bin->left) != -2)
	{
		get_status(0);
		j = get_static_fork(0);
		lecture(shell, bin->right);
	}
	if (bin->type == 2 || bin->type == 3)
	{
		lecture(shell, bin->left);
		j = get_static_fork(0);
		if ((bin->type == 2 && get_status(-2) == 0) ||
		(bin->type == 3 && get_status(-2) != 0))
			lecture(shell, bin->right);
	}
	else if (bin->type == 4)
		bintype2(j, shell, bin);
	return (1);
}
