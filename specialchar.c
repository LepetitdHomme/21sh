/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:59:36 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:30:28 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*set_replace_var(char *src, char *tmp, char **dst, int *count)
{
	char	*ret;

	if (src == NULL || tmp == NULL || *dst == NULL || count == NULL)
		error(0);
	ret = NULL;
	if (ft_strlen(src) - 1 == ft_strlen(tmp))
		return (NULL);
	*count = ft_strlen(*dst) + ft_strlen(src) - 2 - (2 * ft_strlen(tmp));
	if ((ret = (char *)malloc(sizeof(char) * (*count + 1))) == NULL && error(9))
		return (NULL);
	ret[*count] = '\0';
	*count = ft_strlen(tmp) + 1;
	return (ret);
}

int			replace_var(char *src, char *tmp, char **dst, int i)
{
	char	*new;
	int		count;
	int		j;
	int		k;

	if (src == NULL || tmp == NULL || *dst == NULL)
		return (error(0));
	new = NULL;
	if (ft_strlen(src) - 1 == ft_strlen(tmp))
		return (0);
	(new = set_replace_var(src, tmp, dst, &count)) == NULL ? error(9) : 0;
	k = 0;
	j = 0;
	while ((*dst)[j] != '\0')
	{
		if (j >= i && j < (i + (int)ft_strlen(tmp) + 1) && j++)
			while (src[count] != '\0')
				new[k++] = src[count++];
		else
			new[k++] = (*dst)[j++];
	}
	free(*dst);
	*dst = new;
	return (1);
}

int			replace_special_char(t_shell *shell, char **command, int i)
{
	char	*var;
	int		j;
	int		k;

	if (((command == NULL || *command == NULL) && error(0)) ||
	(shell == NULL || shell->environ == NULL))
		return (1);
	k = i;
	j = i;
	while ((*command)[i] != ' ' && (*command)[i] != 39 &&
			(*command)[i] != 34 && (*command)[i])
		i++;
	if (i - j < 2)
		return (1);
	if ((var = ft_strsub(*command, j + 1, i - (j + 1))) == NULL)
		return (error(9));
	j = 0;
	while (shell->environ[j])
	{
		if (ft_strncmp(shell->environ[j], var, ft_strlen(var)) == 0)
			replace_var(shell->environ[j], var, command, k);
		j++;
	}
	free(var);
	return (1);
}

int			specialchar(t_shell *sh, char **com)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (((sh == NULL || *com == NULL) && error(0)) || sh->environ == NULL)
		return (1);
	while (*com && (*com)[i] != '\0')
	{
		if ((*com)[i] == 34 || (*com)[i] == 39)
		{
			j = end_of_quote((*com), i);
			while (++i < j)
			{
				if (tilde(sh, com, i, j) == 0 && (*com)[i] == '$' &&
				(*com)[j] == 34 && replace_special_char(sh, com, i) == 1)
					break ;
			}
		}
		else if (tilde(sh, com, i, -1) == 0 && (*com)[i] == '$')
			replace_special_char(sh, com, i);
		i++;
	}
	return (1);
}
