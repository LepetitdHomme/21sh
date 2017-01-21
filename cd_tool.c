/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:50:56 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 12:08:33 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		test(char *str)
{
	int	i;
	int	ret;

	if (str == NULL)
		return (-1);
	i = 1;
	ret = -1;
	while (str[i] != '\0')
	{
		if (str[i] != 'P' && str[i] != 'L')
			return (-1);
		ret = (str[i] == 'P') ? 1 : 0;
		i++;
	}
	return (ret);
}

char			*get_old(t_shell *sh)
{
	int		old;

	if (sh == NULL)
		return (NULL);
	if ((old = index_pwd(sh->environ, "OLDPWD=")) == -1 ||
	ft_strlen(sh->environ[old]) < 8)
		return (NULL);
	return (ft_strsub(sh->environ[old], 7, ft_strlen(sh->environ[old]) - 7));
}

int				physical_flag(t_shell *sh)
{
	int	i;
	int	ret;

	if (sh == NULL || sh->split == NULL)
		return (-1);
	i = -1;
	ret = -1;
	while (sh->split && sh->split[++i])
	{
		if (ft_strcmp(sh->split[i], "-") == 0 && ret == -1)
			return (2);
		if (ft_strcmp(sh->split[i], "-") == 0 && ret != -1)
			return (-2);
		else if (ft_strncmp(sh->split[i], "-", 1) == 0)
			if (ft_strlen(sh->split[i]) > 1 && (ret = test(sh->split[i])) == -1)
				return (-2);
	}
	return (ret == -1 ? 0 : ret);
}

int				index_directory(char **split)
{
	int	ret;

	if (split == NULL)
		return (-1);
	ret = 1;
	while (split[ret])
	{
		if (split[ret][0] != '-')
			return (ret);
		ret++;
	}
	return (-1);
}

int		set_curpath(char **curpath, char *src, int i)
{
	if (src == NULL)
		return (-1);
	if (i != 1)
		*curpath = ft_strdup(src);
	else
		*curpath = ft_strjoin("./", src);
	return (1);
}
