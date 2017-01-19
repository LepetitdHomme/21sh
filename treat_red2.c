/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_red2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 14:24:09 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 16:53:55 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		through_split(char **split)
{
	int	i;

	if (split == NULL)
		return (-1);
	i = 0;
	while (split && split[i])
	{
		if (split[i][0] != ' ')
			break ;
		i++;
	}
	if (i == (int)count_split(split))
		return (-1);
	return (i);
}

int				open_file(t_redir *redir, int i, int *fd)
{
	char	**file;
	int		lu;
	int		nb;

	if ((redir == NULL || fd == NULL) && error(0))
		return (-1);
	if (i + 1 < (int)ft_strlen(redir->redir) &&
	(redir->type != 3 && redir->type != 4 && redir->redir[i + 1] == '&'))
		i++;
	if ((file = ft_strsplit(&redir->redir[i], ' ')) == NULL)
		return (-1);
	if ((nb = through_split(file)) == -1)
		return (-1);
	lu = -1;
	if (redir->type == 1)
		lu = open(file[nb], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (redir->type == 2)
		lu = open(file[nb], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else if (redir->type == 3)
		lu = heredoc(redir, i);
	else if (redir->type == 4)
		lu = open(file[nb], O_RDONLY, 0644);
	freesplit(file);
	free(file);
	return (lu);
}

static void		fork_dup(int *fd, t_shell *shell, int i)
{
	int	c;

	if (fd == NULL || shell == NULL)
		error(0);
	get_static_fork(1);
	c = fork();
	if (c == 0)
	{
		while (++i < 3)
		{
			if (fd[i] == -2)
				close(i);
			else if (i != fd[i])
				dup2(fd[i], i);
		}
		exe_command(shell);
	}
	else if (c > 0)
	{
		wait(NULL);
		fd[0] = 0;
		fd[1] = 1;
		fd[2] = 2;
	}
}

static int		duplicate(int *fd, t_shell *shell)
{
	int i;

	if (fd == NULL || shell == NULL)
		return (error(0));
	i = -1;
	if (get_static_fork(-1) == 1)
	{
		while (++i < 3)
		{
			if (fd[i] == -2)
				close(i);
			else if (i != fd[i])
				dup2(fd[i], i);
		}
		if (exe_command(shell) == -1 && m_error(2))
			return (0);
	}
	else
		fork_dup(fd, shell, -1);
	return (1);
}

int				fork_redir(int *fd, t_shell *shell)
{
	int i;
	int	forked;

	if (fd == NULL || shell == NULL)
		return (error(0));
	i = -1;
	forked = 0;
	while (++i < 3)
		if (i != fd[i])
			forked = duplicate(fd, shell);
	return (forked);
}
