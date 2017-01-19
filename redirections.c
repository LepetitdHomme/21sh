/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:35:17 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 16:53:40 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (-1);
}

int	save_redir(t_shell *shell, int j, int k, char *r)
{
	char	*redir;
	t_redir	*new_redir;
	t_redir	*vag;

	if (shell == NULL || r == NULL || j > (int)ft_strlen(r) ||
	k > (int)ft_strlen(r))
		return (error(0));
	if ((k - j) <= 0 || (redir = ft_strsub(r, j, k - j + 1)) == NULL ||
	(new_redir = (t_redir *)malloc(sizeof(t_redir))) == NULL)
		return (error(9));
	new_redir->redir = redir;
	new_redir->next = NULL;
	new_redir->type = -1;
	if (shell->redir == NULL)
	{
		shell->redir = new_redir;
		new_redir->prev = NULL;
		return (1);
	}
	vag = shell->redir;
	while (vag && vag->next)
		vag = vag->next;
	vag->next = new_redir;
	new_redir->prev = vag;
	return (1);
}

char	*less_redir(char *ret, int j, int k)
{
	char	*less;
	int		count;
	int		i;
	int		l;

	if (ret == NULL || k >= (int)ft_strlen(ret))
		return (NULL);
	count = (int)ft_strlen(ret) - (k - j + 1);
	i = 0;
	l = 0;
	if ((count == 0 && error(19)) ||
	((less = (char *)malloc(sizeof(char) * (count + 1))) == NULL && error(9)))
		return (NULL);
	while (i < (int)ft_strlen(ret))
	{
		if (i < j || i > k)
		{
			less[l] = ret[i];
			l++;
		}
		i++;
	}
	less[count] = '\0';
	free(ret);
	return (less);
}
