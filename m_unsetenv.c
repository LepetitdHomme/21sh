/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 13:36:43 by csellier          #+#    #+#             */
/*   Updated: 2016/11/24 11:28:11 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		which(t_shell *shell, int k)
{
	int		i;
	int		chri;
	char	*tmp;

	if (shell == NULL || shell->split == NULL)
		return (-1);
	i = 0;
	while (shell->environ && shell->environ[i])
	{
		if ((chri = ft_strchri(shell->environ[i], '=')) >= 0)
		{
			tmp = ft_strsub(shell->environ[i], 0, chri);
			if (ft_strcmp(shell->split[k], tmp) == 0)
			{
				free(tmp);
				return (i);
			}
			free(tmp);
		}
		i++;
	}
	return (-1);
}

int		m_boucle(char **env, char **new_env, int which, int limite)
{
	int		j;
	int		i;

	if (env == NULL || new_env == NULL)
		return (-1);
	i = 0;
	j = 0;
	while (j < limite)
	{
		if ((size_t)(i) < count_split(env) && i == which)
			i++;
		new_env[j] = ft_strdup(env[i]);
		j++;
		i++;
	}
	return (1);
}

int		ft_dzero(char **split, int b)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (-1);
	while (i < b)
	{
		split[i] = NULL;
		i++;
	}
	return (1);
}

int		ft_unset_env(char **split, t_shell *shell, int i)
{
	int		a;
	int		b;
	char	**new_env;

	if (split == NULL || shell == NULL)
		return (1);
	if ((b = ft_count(shell->environ)) <= 0)
		return (m_error(8));
	if ((a = which(shell, i)) == -1)
		return (m_error(8));
	if ((new_env = (char **)malloc(sizeof(char *) * (b + 1))) == NULL)
		return (1);
	new_env[b] = NULL;
	ft_dzero(new_env, b);
	m_boucle(shell->environ, new_env, a, b);
	freesplit(shell->environ);
	free(shell->environ);
	shell->environ = ft_copy_split(new_env);
	freesplit(new_env);
	free(new_env);
	return (0);
}
