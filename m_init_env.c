/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:49 by csellier          #+#    #+#             */
/*   Updated: 2016/11/29 16:57:31 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_init_environ(t_shell *shell)
{
	if (shell == NULL)
		return (-1);
	if ((shell->environ = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (-1);
	shell->environ[0] = NULL;
	shell->environ[1] = NULL;
	return (1);
}

int		struct_show_env(t_shell *v2, char **v1, char **envv1)
{
	if (v2 == NULL || v1 == NULL)
		return (-1);
	v2->environ = ft_copy_split(envv1);
	v2->split = ft_copy_split(v1);
	v2->prompt = NULL;
	v2->path = NULL;
	v2->redir = NULL;
	ft_init_path(v2);
	return (1);
}

int		ft_init_path(t_shell *shell)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (shell == NULL)
		return (-1);
	while (shell->environ && shell->environ[i])
	{
		if (ft_strncmp(shell->environ[i], "PATH=", 5) == 0)
		{
			if ((tmp = ft_strsub(shell->environ[i], 5,
							ft_strlen(shell->environ[i]) - 5)) == NULL)
				return (-1);
			if (shell->path != NULL && freesplit(shell->path))
				free(shell->path);
			if ((shell->path = ft_strsplit(tmp, ':')) == NULL)
				return (-1);
			free(tmp);
		}
		i++;
	}
	return (1);
}

int		ft_look4flag(t_shell *shell)
{
	if (shell == NULL || shell->split == NULL)
		return (-1);
	if (ft_strncmp(shell->split[1], "-", 1) == 0)
		return (m_error(14));
	return (-1);
}

int		ft_access(char *path)
{
	if (path == NULL)
		return (1);
	if (access(path, F_OK) == 0)
		if (access(path, X_OK) != 0)
			return (m_error(13));
	return (m_error(12));
}
