/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:50:56 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 12:08:33 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The cd utility shall change the working directory of the current shell
** execution environment
*/

#include "ft_21sh.h"

static int		new_curpath(t_shell *sh, char **path)
{
	char	*new;
	char	*tmp;
	int		pwd;

	if (sh == NULL || sh->environ == NULL || path == NULL || *path == NULL)
		return (-1);
	if ((pwd = index_pwd(sh->environ, "PWD=")) == -1 ||
	ft_strlen(sh->environ[pwd]) < 5)
		return (1);
	tmp = ft_strsub(sh->environ[pwd], 4, ft_strlen(sh->environ[pwd]) - 4);
	if (tmp[ft_strlen(tmp) - 1] == '/')
	{
		new = ft_strjoin(tmp, *path);
		free(tmp);
		free(*path);
		*path = new;
		return (0);
	}
	new = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = ft_strjoin(new, *path);
	free(new);
	free(*path);
	*path = tmp;
	return (0);
}

int				join_old_and_path(t_shell *sh, char *path, int old)
{
	char	*tmp;
	char	*tmp2;
	int		pwd;

	if (sh == NULL || sh->environ == NULL || path == NULL)
		return (1);
	if (ft_strlen(sh->environ[old]) < 8)
		tmp = NULL;
	else
		tmp = ft_strsub(sh->environ[old], 7, ft_strlen(sh->environ[old]) - 7);
	tmp2 = ft_strjoin(tmp, "/");
	if (tmp)
		free(tmp);
	tmp = ft_strjoin(tmp2, path);
	free(tmp2);
	pwd = index_pwd(sh->environ, "PWD=");
	if (pwd == -1)
		doesnt(sh, "PWD=", tmp);
	else
	{
		free(sh->environ[pwd]);
		sh->environ[pwd] = ft_strjoin("PWD=", tmp);
	}
	free(tmp);
	return (1);
}

static int		cd_2(t_shell *sh, char **curpath)
{
	int		p_flag;

	if (sh == NULL || *curpath == NULL)
		return (1);
	if ((p_flag = physical_flag(sh)) == -2)
		return (m_error(23));
	if (p_flag == 2)
		as_old(sh, curpath);
	if (p_flag == 0 && (*curpath)[0] != '/')
		new_curpath(sh, curpath);
	if (chdir(*curpath) != 0)
	{
		ft_access(*curpath);
		free(*curpath);
		return (0);
	}
	set_old(sh);
	set_pwd(sh, p_flag, *curpath);
	free(*curpath);
	treat_pwd(sh);
	return (0);
}

int				cd(t_shell *sh)
{
	char	*curpath;
	char	*d;
	int		idir;
	int		ihom;

	if (sh == NULL || sh->split == NULL)
		return (1);
	if ((idir = index_directory(sh->split)) == -1 &&
	((ihom = index_pwd(sh->environ, "HOME=")) == -1 ||
	6 > ft_strlen(sh->environ[ihom])) && physical_flag(sh) != 2 && m_error(22))
		return (0);
	curpath = NULL;
	if (physical_flag(sh) == 2 && (d = get_old(sh)) == NULL && m_error(12))
		return (0);
	if (physical_flag(sh) != 2 && idir == -1 && ihom != -1)
		d = ft_strsub(sh->environ[ihom], 5, ft_strlen(sh->environ[ihom]) - 5);
	else if (physical_flag(sh) != 2)
		d = ft_strdup(sh->split[idir]);
	if (d[0] == '/' || d[0] == '.' || (ft_strlen(d) >= 2 &&
	ft_strncmp(d, "..", 2) == 0))
		set_curpath(&curpath, d, 0);
	else
		set_curpath(&curpath, d, 1);
	free(d);
	return (cd_2(sh, &curpath));
}
