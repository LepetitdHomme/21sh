/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tool2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:50:56 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 12:08:33 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			as_old(t_shell *sh, char **curpath)
{
	int	old;

	if (sh == NULL || sh->environ == NULL || *curpath == NULL)
		return (-1);
	if ((old = index_pwd(sh->environ, "OLDPWD=")) == -1)
		return (-1);
	free(*curpath);
	if (ft_strlen(sh->environ[old]) < 8)
		return (-1);
	*curpath = ft_strsub(sh->environ[old], 7, ft_strlen(sh->environ[old]) - 7);
	ft_putstr_fd("PWD=", get_env(NULL)->fd);
	ft_putendl_fd(*curpath, get_env(NULL)->fd);
	return (1);
}

static int	set_pwd2(t_shell *sh, char *curpath, int p_flag)
{
	int		old;

	if (sh == NULL || sh->environ == NULL || curpath == NULL)
		return (1);
	if ((old = index_pwd(sh->environ, "OLDPWD=")) == -1)
	{
		m_error(24);
		return (set_pwd(sh, 1, curpath));
	}
	if (p_flag == 2)
		return (as_path(sh, curpath));
	return (join_old_and_path(sh, curpath, old));
}

int			set_pwd(t_shell *sh, int p_flag, char *curpath)
{
	int		pwd;
	char	*tmp;

	if (sh == NULL || sh->environ == NULL || curpath == NULL)
		return (1);
	if (is_root(sh, curpath, p_flag) == 0)
		return (1);
	tmp = NULL;
	pwd = index_pwd(sh->environ, "PWD=");
	if (p_flag == 1)
	{
		tmp = getcwd(tmp, 1024);
		if (pwd == -1)
			doesnt(sh, "PWD=", tmp);
		else
		{
			free(sh->environ[pwd]);
			sh->environ[pwd] = ft_strjoin("PWD=", tmp);
		}
	}
	else
		set_pwd2(sh, curpath, p_flag);
	if (tmp)
		free(tmp);
	return (1);
}

static int	set_old2(t_shell *sh, int pwd, int old)
{
	char	*tmp;

	if (sh == NULL || sh->environ == NULL)
		return (1);
	tmp = ft_strsub(sh->environ[pwd], 4, ft_strlen(sh->environ[pwd]) - 4);
	if (old == -1)
		doesnt(sh, "OLDPWD=", tmp);
	else
	{
		free(sh->environ[old]);
		sh->environ[old] = ft_strjoin("OLDPWD=", tmp);
	}
	free(tmp);
	return (1);
}

int			set_old(t_shell *sh)
{
	int		old;
	int		pwd;

	if (sh == NULL || sh->environ == NULL)
		return (-1);
	old = index_pwd(sh->environ, "OLDPWD=");
	pwd = index_pwd(sh->environ, "PWD=");
	if (pwd == -1 || ft_strlen(sh->environ[pwd]) <= 4)
	{
		if (old != -1)
		{
			free(sh->environ[old]);
			sh->environ[old] = ft_strdup("OLDPWD=");
		}
		else
			doesnt(sh, "OLDPWD", "=");
	}
	else if (pwd != -1)
		set_old2(sh, pwd, old);
	return (1);
}
