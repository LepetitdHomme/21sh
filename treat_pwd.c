/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:30:29 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:30:47 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char		*end_copy(char *str, char **split, int i)
{
	char	*tmp;

	if (split == NULL)
		return (NULL);
	if (i + 2 > (int)count_split(split) - 1)
		return (str);
	i += 2;
	tmp = NULL;
	while (split && split[i])
	{
		tmp = ft_strjoin(str, "/");
		free(str);
		str = NULL;
		str = ft_strjoin(tmp, split[i]);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (str);
}

static int		normal_copy(char **dst, char *src)
{
	char	*tmp;

	if (dst == NULL)
		return (0);
	tmp = NULL;
	if (*dst)
		tmp = ft_strjoin(*dst, "/");
	else
		tmp = ft_strdup("/");
	if (*dst)
	{
		free(*dst);
		*dst = NULL;
	}
	*dst = ft_strjoin(tmp, src);
	if (tmp)
		free(tmp);
	return (1);
}

static char		*treat_str(char *string, int i)
{
	char	*str;
	char	**s;

	if (string == NULL || (s = ft_strsplit(string, '/')) == NULL)
		return (NULL);
	free(string);
	str = NULL;
	while (s && s[i])
	{
		if (ft_strcmp(s[i], ".") != 0 && ft_strcmp(s[i], "..") != 0)
		{
			if (i + 1 < (int)count_split(s) && ft_strcmp(s[i + 1], "..") == 0)
			{
				str = treat_str(end_copy(str, s, i), 0);
				break ;
			}
			else
				normal_copy(&str, s[i]);
		}
		i++;
	}
	freesplit(s);
	free(s);
	return (str);
}

int				treat_pwd(t_shell *sh)
{
	char	*s;
	int		p;

	if (sh == NULL || sh->environ == NULL ||
	(p = index_pwd(sh->environ, "PWD=")) == -1 ||
	ft_strlen(sh->environ[p]) < 5 ||
	(s = ft_strsub(sh->environ[p], 4, ft_strlen(sh->environ[p]) - 4)) == NULL)
		return (1);
	if ((s = treat_str(s, 0)) == NULL)
		return (1);
	free(sh->environ[p]);
	sh->environ[p] = ft_strjoin("PWD=", s);
	free(s);
	return (0);
}
