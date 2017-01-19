/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:50:56 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 12:08:33 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		as_path(t_shell *sh, char *curpath)
{
	int	pwd;

	if (sh == NULL || sh->environ == NULL || curpath == NULL)
		return (1);
	if ((pwd = index_pwd(sh->environ, "PWD=")) == -1)
		doesnt(sh, "PWD=", curpath);
	else
	{
		free(sh->environ[pwd]);
		sh->environ[pwd] = NULL;
		sh->environ[pwd] = ft_strjoin("PWD=", curpath);
	}
	return (1);
}

char	*get_prompt(char *prompt)
{
	static char	*ret = NULL;

	if (prompt != NULL)
	{
		if (ret != NULL)
			free(ret);
		ret = ft_strdup(prompt);
	}
	return (ret);
}
