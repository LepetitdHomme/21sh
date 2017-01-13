/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:59:40 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:35:55 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				free_gnl(char *line, char **end, int bol, int fd)
{
	if (bol == 1)
		free(line);
	freesplit(end);
	free(end);
	close(fd);
	if ((fd = open("/tmp/heredoc", O_RDWR)) == -1)
		return (-1);
	return (fd);
}

int				heredoc(t_redir *redir, int i)
{
	int		fd;
	char	**end;
	char	*line;

	if ((fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
		return (-1);
	if (redir == NULL || (end = ft_strsplit(&redir->redir[i], ' ')) == NULL)
		return (-1);
	line = NULL;
	ft_putstr_fd("heredoc >", get_env(NULL)->fd);
	while (get_next_line(get_stdin(-1), &line) != 0)
	{
		if (ft_strcmp(line, end[0]) == 0)
			return (free_gnl(line, end, 1, fd));
		ft_putendl_fd(line, fd);
		ft_putstr_fd("heredoc >", get_env(NULL)->fd);
		free(line);
	}
	ft_putchar_fd('\n', get_env(NULL)->fd);
	return (free_gnl(line, end, 0, fd));
}
