/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:26 by csellier          #+#    #+#             */
/*   Updated: 2016/11/23 13:59:48 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				cd_noflag(t_shell *shell)
{
	int	home;
	int	i;
	int	ch;

	home = -1;
	i = 0;
	ch = -2;
	if (shell == NULL || shell->environ == NULL)
		return (-1);
	while (shell->environ[i])
	{
		if (ft_strncmp(shell->environ[i], "HOME=", 5) == 0)
			home = i;
		i++;
	}
	if (home != -1 && (ch = chdir(shell->environ[home] + 5)) == 0)
	{
		ft_pwd(shell, -1, -1);
		return (1);
	}
	if (ch != 0)
		return (m_error(12));
	return (-1);
}

int				ft_chdir(t_shell *sh, char *path, char **y, int i)
{
	int	ch;

	ch = -1;
	if (sh == NULL)
		return (-1);
	if (i == 0)
	{
		if ((ch = chdir(path)) == 0)
			return (1);
		return (ft_access(path));
	}
	ch = 0;
	while (sh->environ && sh->environ[ch])
	{
		if (ft_strncmp(sh->environ[ch], "HOME=", 5) == 0)
		{
			*y = ft_strsub(sh->environ[ch], 5, ft_strlen(sh->environ[ch]) - 5);
			break ;
		}
		ch++;
	}
	return (1);
}

int				ft_pwd(t_shell *shell, int pwd, int old)
{
	char	*tmp;

	if (shell == NULL || shell->environ == NULL || shell->environ[0] == '\0')
		return (-1);
	old = index_pwd(shell->environ, "OLDPWD=");
	pwd = index_pwd(shell->environ, "PWD=");
	if (pwd == -1)
		return (1);
	tmp = ft_strsub(shell->environ[pwd], 4, ft_strlen(shell->environ[pwd]) - 4);
	if (old != -1)
	{
		free(shell->environ[old]);
		shell->environ[old] = ft_strjoin("OLDPWD=", tmp);
	}
	else
		doesnt(shell, "OLDPWD=", tmp);
	free(tmp);
	tmp = NULL;
	free(shell->environ[pwd]);
	tmp = getcwd(tmp, 1024);
	shell->environ[pwd] = ft_strjoin("PWD=", tmp);
	free(tmp);
	return (1);
}

int				ft_oldcd(t_shell *shel, int i, int old, int pwd)
{
	char	*tmp;
	char	*tmp2;

	if (shel == NULL || shel->environ == NULL || shel->environ[i] == '\0')
		return (-1);
	while (shel->environ[i])
	{
		if (ft_strncmp(shel->environ[i], "OLDPWD=", 7) == 0)
			old = i;
		else if (ft_strncmp(shel->environ[i], "PWD=", 4) == 0)
			pwd = i;
		i++;
	}
	tmp = ft_strsub(shel->environ[old], 7, ft_strlen(shel->environ[old]) - 7);
	tmp2 = ft_strsub(shel->environ[pwd], 4, ft_strlen(shel->environ[pwd]) - 4);
	free(shel->environ[old]);
	shel->environ[old] = ft_strjoin("OLDPWD=", tmp2);
	free(shel->environ[pwd]);
	shel->environ[pwd] = ft_strjoin("PWD=", tmp);
	ft_chdir(shel, tmp, NULL, 0);
	free(tmp);
	free(tmp2);
	return (1);
}

int				ft_cd(t_shell *sh, int arg)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	if (sh == NULL)
		return (-1);
	if ((arg = ft_count(sh->split)) < 2)
		return (cd_noflag(sh));
	if (ft_strncmp(sh->split[1], "~", 1) == 0 && ft_chdir(sh, NULL, &tmp, 1) &&
	(s = ft_strjoin(tmp, sh->split[1] + 1)) != NULL)
		free(tmp);
	else
		s = ft_strdup(sh->split[1]);
	if (arg >= 2 && ft_strncmp(sh->split[1], "-", 1) != 0)
	{
		ft_chdir(sh, s, NULL, 0);
		ft_pwd(sh, -1, -1);
		free(s);
	}
	else if ((arg >= 2 && ft_strcmp(s, "-") == 0 && ft_oldcd(sh, 0, 0, 0) == 1)
	|| ft_look4flag(sh) != -2)
		free(s);
	return (1);
}
