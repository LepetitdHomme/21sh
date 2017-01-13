/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:35 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 11:47:03 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_see_next(t_shell *shell, t_shell *shell2, int i)
{
	if (shell == NULL || shell2 == NULL)
		return (1);
	if (!(shell->split[i + 1]))
	{
		return (m_error(7));
	}
	if (ft_strchri(shell->split[i + 1], '=') != -1)
		return (m_error(7));
	ft_unset_env(shell->split, shell2, i + 1);
	return (1);
}

int		ft_export_2(t_shell *shell, t_shell *shell2, int i)
{
	char		*tmp;
	char		*tmp2;
	int			chri;

	if (shell == NULL || shell2 == NULL)
		return (-1);
	if ((chri = ft_strchri(shell->split[i], '=')) <= 0)
		return (m_error(10));
	tmp = ft_strsub(shell->split[i], 0, chri + 1);
	if ((size_t)chri == ft_strlen(shell->split[i]))
		tmp2 = NULL;
	else
		tmp2 = ft_strsub(shell->split[i], chri + 1,
				ft_strlen(shell->split[i]) - (chri + 1));
	if (ft_setenv(shell2, tmp, tmp2, 1) == -1)
		return (-1);
	free(tmp);
	free(tmp2);
	return (1);
}

int		display_env(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (-1);
	while (split[i])
	{
		ft_putendl_if(split[i]);
		i++;
	}
	return (1);
}

int		exe_command_2(t_shell *shell, t_shell *shell2, int i)
{
	if (shell == NULL || shell2 == NULL)
		return (-1);
	if (shell2->split != NULL)
	{
		freesplit(shell2->split);
		free(shell2->split);
		shell2->split = NULL;
	}
	shell2->split = ft_copy_split(&shell->split[i]);
	exe_command(shell2);
	free_ft_env(shell2);
	return (1);
}

int		ft_env(t_shell *shell)
{
	int			i;
	t_shell		shell2;

	i = 0;
	struct_show_env(&shell2, shell->split, shell->environ);
	while (++i < ft_count(shell->split))
	{
		if (ft_strcmp(shell->split[i], "-i") == 0 && freesplit(shell2.environ))
		{
			free(shell2.environ);
			shell2.environ = NULL;
		}
		else if (ft_strcmp(shell->split[i], "-u") == 0)
		{
			i += 1 + ft_see_next(shell, &shell2, i);
			continue;
		}
		else if (ft_strchri(shell->split[i], '=') != -1)
			ft_export_2(shell, &shell2, i);
		else if (exe_command_2(shell, &shell2, i))
			return (1);
	}
	display_env(shell2.environ);
	free_ft_env(&shell2);
	return (1);
}
