/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:14:59 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:12:52 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		check_redir(char *s, int i)
{
	int j;

	if (s == NULL)
		return (-2);
	j = i;
	while (s[i] && is_redir(s[i]) != -1)
		i++;
	if ((i - j) > 2)
		return (-1);
	return (1);
}

int		which_type(char *s)
{
	size_t	i;

	if (s == NULL)
		return (error(0));
	i = 0;
	while (s && ft_isdigit(s[i]) == 1)
		i++;
	if (is_redir(s[i]) == -1 && m_error(15))
		return (-1);
	if (check_redir(s, i) == -1 && m_error(19))
		return (-1);
	if (s[i] == '>' && (i + 1) <= ft_strlen(s) && s[i + 1] == '>')
		return (1);
	else if (s[i] == '>' && (i + 1) <= ft_strlen(s) && s[i + 1] != '>')
		return (2);
	else if (s[i] == '<' && (i + 1) <= ft_strlen(s) && s[i + 1] == '<')
		return (3);
	else if (s[i] == '<' && (i + 1) <= ft_strlen(s) && s[i + 1] != '<')
		return (4);
	return (-1);
}

int		find_fd2(int *fd, t_redir *red, int i)
{
	int	len;

	if (fd == NULL || red == NULL || red->redir == NULL || red->type == -1)
		return (error(0));
	quoteless(&red->redir, i, 0, 0);
	len = ft_strlen(red->redir);
	if (red->redir[i] == '&' && (i + 1) < len && red->type != 3)
	{
		if (red->redir[i + 1] == '1' && i + 2 >= len)
			return (1);
		else if (red->redir[i + 1] == '2' && i + 2 >= len)
			return (2);
		else if (red->redir[i + 1] == '-')
			return (-2);
		i++;
	}
	if (red->redir[i] && (i + 1) <= len)
		return (open_file(red, i, fd));
	return (-1);
}

int		find_fd(t_redir *red, int *fd)
{
	int	i;
	int	file;

	if (red == NULL || red->type == -1 || fd == NULL)
		return (-1);
	i = 0;
	file = (red->type == 4 || red->type == 3) ? 0 : 1;
	if (ft_isdigit(red->redir[i]) == 1)
	{
		if (file == 0 || (file = ft_atoi(&red->redir[i])) > 2 || file < 0)
			return (m_error(16));
		while (ft_isdigit(red->redir[i]) == 1 && red->redir[i])
			i++;
	}
	else if (is_redir(red->redir[i]) == -1)
		return (m_error(15));
	while (red->redir[i] && is_redir(red->redir[i]) == 1)
		i++;
	if (i + 1 >= (int)ft_strlen(red->redir) || (i = find_fd2(fd, red, i)) == -1)
		return (m_error(15));
	fd[file] = i;
	return (0);
}

int		treat_redir(t_shell *shell)
{
	t_redir	*vag;
	int		i;
	int		fd[3];

	if (shell == NULL)
		return (error(0));
	if (shell->redir == NULL)
		return (0);
	fd[0] = 0;
	fd[1] = 1;
	fd[2] = 2;
	vag = shell->redir;
	i = 0;
	while (vag)
	{
		if ((vag->type = which_type(vag->redir)) == -1)
			return (-1);
		if ((i = find_fd(vag, &fd[0])) != 0)
			return (-1);
		vag = vag->next;
	}
	return (fork_redir(&fd[0], shell));
}
