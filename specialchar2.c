/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialchar2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:42:32 by csellier          #+#    #+#             */
/*   Updated: 2017/03/15 18:09:13 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_bang(char *com, int i)
{
	if (com == NULL)
		return (1);
	if (i + 2 >= (int)ft_strlen(com) || com[i + 1] == 32 || com[i + 1] == 9 ||
			com[i + 1] == '\n')
		return (1);
	return (0);
}

static int	bangless(char *com, int i)
{
	int	len;
	int	end;

	if (com == NULL || i + 1 >= (len = (int)ft_strlen(com)))
		return (0);
	end = i;
	while (i < len && com[i] != 32 && com[i] != 9 && com[i] != '\n')
		i++;
	return (end - i);
}

static int	replace_bang(char **com, int *i, t_com *l)
{
	char	*str;
	char	*new;
	int		lentmp;
	int		len;
	int		j;

	if (com == NULL || (*com) == NULL || i == NULL || l == NULL)
		return (1);
	if ((str = list2str(l)) == NULL)
		return (1);
	lentmp = bangless(*com, *i);
	len = ft_strlen(str) + ft_strlen(*com) - lentmp;
	if ((new = (char *)malloc(sizeof(char) * (len))) == NULL)
	{
		free(str);
		return (1);
	}
	j = 0;
	while (j < len)
	{
		if (j < *i)
		   new[j] = (*com)[*i];
		else if (j >= *i && j < *i + (int)ft_strlen(str))
			new[j] = str[j - *i];
		else
			new[j] = (*com)[j - (int)ft_strlen(str)];
		j++;
	}
	free(str);
	free(*com);
	*com = new;
	*i += (int)ft_strlen(str);
	return (0);
}

int			specialchar2(t_shell *sh, char **com)
{
	int	i;

	if (((sh == NULL || *com == NULL) && error(0)) || sh->environ == NULL)
		return (1);
	i = 0;
	while (*com && (*com)[i] != '\0')
	{
			if ((*com)[i] == 39)
				i = end_of_quote((*com), i);
			if ((*com)[i] == '!' && check_bang(*com, i) == 0)
				replace_bang(com, &i, bang(*com, i));
			i++;
	}
	return (0);
}
