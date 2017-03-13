/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:59:36 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:32:13 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	replace_tilde(char *src, char **dst, int i)
{
	char	*new;
	size_t	len;
	int		k;
	int		l;

	if (src == NULL || dst == NULL || *dst == NULL || 6 > ft_strlen(src))
		return (0);
	len = ft_strlen(*dst) - 1 + ft_strlen(src) - 5;
	if ((new = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (0);
	new[len] = '\0';
	len = 0;
	k = 0;
	l = 5;
	while ((*dst)[len] != '\0')
	{
		if ((int)len < i || (int)len > i)
			new[k++] = (*dst)[len++];
		else if ((int)len == i && len++)
			while (src[l] != '\0')
				new[k++] = src[l++];
	}
	free(*dst);
	*dst = new;
	return (0);
}

int			tilde(t_shell *sh, char **com, int i, int j)
{
	int	h;

	if (sh == NULL || sh->environ == NULL || com == NULL || *com == NULL)
		return (0);
	if ((*com)[i] != '~')
		return (0);
	if ((h = index_pwd(sh->environ, "HOME=")) == -1)
		return (0);
	if ((j >= 0 && (*com)[j] == 34) || j == -1)
		return (replace_tilde(sh->environ[h], com, i));
	return (0);
}
