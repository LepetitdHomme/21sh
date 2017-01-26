/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:23:33 by csellier          #+#    #+#             */
/*   Updated: 2016/11/29 17:31:47 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		exist(t_shell *shell, int k, char *value)
{
	int		chri;
	int		size;
	char	*tmp;

	tmp = NULL;
	if (shell == NULL)
		return (-1);
	if ((chri = ft_strchri(shell->environ[k], '=')) == 0)
		return (-1);
	if ((size = chri + 1 + ft_strlen(value)) <= 0)
		return (-1);
	if ((tmp = ft_strsub(shell->environ[k], 0, chri + 1)) == NULL)
		return (-1);
	free(shell->environ[k]);
	if ((shell->environ[k] = ft_strjoin(tmp, value)) == NULL)
		return (-1);
	free(tmp);
	return (1);
}

int		ft_count(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (-1);
	while (split[i])
		i++;
	return (i);
}

int		doesnt(t_shell *shll, char *name, char *value)
{
	int		count;
	char	**tmp;
	int		i;

	i = 0;
	if (shll == NULL || shll->environ == NULL || name == NULL)
		return (-1);
	if ((count = ft_count(shll->environ)) < 0)
		return (-1);
	tmp = ft_copy_split(shll->environ);
	freesplit(shll->environ);
	free(shll->environ);
	if ((shll->environ = (char **)malloc(sizeof(char *) * (count + 2))) == NULL)
		return (-1);
	while (i < count)
	{
		shll->environ[i] = ft_strdup(tmp[i]);
		i++;
	}
	freesplit(tmp);
	free(tmp);
	if ((shll->environ[count] = ft_strjoin(name, value)) == NULL)
		return (-1);
	shll->environ[count + 1] = NULL;
	return (1);
}

int		ft_setenv(t_shell *shell, char *name, char *value, int w)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	if (shell == NULL || name == NULL)
		return (-1);
	if (shell->environ == NULL || !shell->environ[i])
		ft_init_environ(shell);
	while (shell->environ[i])
	{
		if (ft_strncmp(shell->environ[i], name, ft_strlen(name)) == 0)
			k = i;
		i++;
	}
	if (k != -1 && w != 0)
		if (exist(shell, k, value) == -1)
			return (-1);
	if (k == -1)
		if (doesnt(shell, name, value) == -1)
			return (-1);
	return (1);
}

int		ft_export(t_shell *shell)
{
	int		chri;
	char	*tmp;
	char	*tmp2;

	if (shell == NULL)
		return (1);
	if (check_param(shell, 2) == 0)
		return (1);
	if ((chri = ft_strchri(shell->split[1], '=')) <= 0)
		return (m_error(10));
	tmp = ft_strsub(shell->split[1], 0, chri + 1);
	if ((size_t)chri == ft_strlen(shell->split[1]) - 1)
		tmp2 = NULL;
	else
		tmp2 = ft_strsub(shell->split[1],
			chri + 1, ft_strlen(shell->split[1]) - chri);
	if (ft_setenv(shell, tmp, tmp2, 1) == -1)
		return (1);
	free(tmp);
	free(tmp2);
	return (0);
}
