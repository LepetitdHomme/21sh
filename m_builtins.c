/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:17 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:51:52 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			freesplit(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (1);
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	return (1);
}

static int	w(t_shell *shell)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	if ((tmp = ft_strjoin("/", shell->split[0])) == NULL)
		return (-1);
	while (shell->path && shell->path[i])
	{
		if ((join = ft_strjoin(shell->path[i], tmp)) == NULL)
			return (-1);
		if (access(join, F_OK) == 0)
		{
			free(tmp);
			free(join);
			return (i);
		}
		free(join);
		i++;
	}
	free(tmp);
	return (-1);
}

int			ret_fils(int status)
{
	if (WIFSIGNALED(status))
	{
		ft_putstr_fd(ROUGE, 2);
		if (WTERMSIG(status) == SIGSEGV)
			ft_putstr_fd("segmentation violation", 2);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("program interrupted", 2);
		else if (WTERMSIG(status) == SIGABRT)
			ft_putstr_fd("program aborted", 2);
		else if (WTERMSIG(status) == SIGTERM)
			ft_putstr_fd("program killed", 2);
		ft_putstr_fd(END, 2);
		ft_signal(1);
	}
	return (1);
}

int			mowgli(char *path, t_shell *shell)
{
	pid_t	i;
	int		c;

	if (path == NULL || shell == NULL)
		return (-1);
	if (access(path, F_OK) != 0 && m_error(5))
		return (ft_putendl_fd(shell->split[0], 2));
	if (access(path, X_OK) != 0 && m_error(13))
		return (ft_putendl_fd(shell->split[0], 2));
	signal(SIGINT, ft_signal);
	if (get_static_fork(-1) == 1)
		execve(path, shell->split, shell->environ);
	i = fork();
	if (i == 0)
		execve(path, shell->split, shell->environ);
	else if (i > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&c);
		exit_status(c);
	}
	signal(SIGINT, SIG_IGN);
	return (1);
}

int			exe_command(t_shell *s)
{
	char	*path;
	char	*tmp;
	int		b;

	if (s == NULL || s->split == NULL)
		return (-1);
	if (is_a_builtin(s) != -2)
		return (1);
	path = NULL;
	tmp = NULL;
	if (ft_strncmp(s->split[0], ".", 1) == 0 ||
	ft_strncmp(s->split[0], "/", 1) == 0)
		path = ft_strdup(s->split[0]);
	else if ((b = w(s)) == -1 && m_error(5) && ft_putendl_fd(s->split[0], 2))
		return (-1);
	else
	{
		if ((tmp = ft_strjoin("/", s->split[0])) == NULL ||
		(path = ft_strjoin(s->path[b], tmp)) == NULL)
			return (-1);
		free(tmp);
	}
	mowgli(path, s);
	free(path);
	return (1);
}
