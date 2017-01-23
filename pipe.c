/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:13:26 by csellier          #+#    #+#             */
/*   Updated: 2016/11/23 13:59:48 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** 0 == command
** 1 == ;
** 2 == &&
** 3 == ||
** 4 == |
*/

static int	set_next_type(char *list, int i, int *index, int type)
{
	int		len;

	if (list == NULL || index == NULL)
		return (-1);
	len = (int)ft_strlen(list);
	*index = i;
	if (type == 1)
		return (1);
	else if (type == 2 && i + 1 < len)
	{
		if (list[i + 1] != '&' && m_error(20))
			return (-1);
		return (2);
	}
	else if (type == 3 && i + 1 < len && list[i + 1] == '|')
		return (3);
	else if (type== 4 && i + 1 < len && list[i + 1] != '|')
		return (4);
	return (-1);
}

static int	get_next_type(char *list, int *index, char c, int type)
{
	int		i;
	int		next;

	if (list == NULL || index == NULL)
		return (error(0));
	i = -1;
	while (list && list[++i])
	{
		if (is_quote(list[i]) != -1)
			i = end_of_quote(list, i);
		if (list[i] == c)
			if ((next = set_next_type(list, i, index, type)) != -1)
				return (next);
	}
	if (c == ';')
		return (get_next_type(list, index, '|', 3));
	else if (c == '|' && type == 3)
		return (get_next_type(list, index, '&', 2));
	else if (c == '&')
		return (get_next_type(list, index, '|', 4));
	return (0);
}

static int	check_com_for_bintree(char *list)// raajouter la gestion des qutoes
{
	int		i;
	int		c;
	int		len;

	if (list == NULL)
		return (error(0));
	i = 0;
	c = 0;
	len = (int)ft_strlen(list);
	while (list && list[i])
	{
		c = which_operand(list[i]);
		if (c == 1 && ((i - 1 >= 0 && which_operand(list[i - 1]) != 0) ||
		(i + 1 < len && which_operand(list[i + 1]) != 0)))
			return (m_error(20));
		else if ((c == 2 || c == 3) && (i == 0 || (i + 1 < len &&
		(which_operand(list[i + 1]) == 1 || which_operand(list[i + 1]) == 4))))
			return (m_error(20));
		i++;
	}
	return (0);
}

static char	*get_sub(char *list, int index, int type, int k)
{
	int		i;
	int		len;

	if (list == NULL && error(0))
		return (NULL);
	if (type <= 0 || type > 4)
		return (NULL);
	i = 0;
	len = index;
	if (k == 1 && (type == 1 || type == 4))
	{
		if (index + 1 > (int)ft_strlen(list))
			return (NULL);
		i = index + 1;
		len = ft_strlen(list) - index;
	}
	else if (k == 1 && (type == 2 || type == 3))
	{
		if (index + 2 > (int)ft_strlen(list))
			return (NULL);
		i = index + 2;
		len = ft_strlen(list) - (index + 1);
	}
	return (ft_strsub(list, i, len));
}

t_bin		*ft_pipe(char *list)
{
	t_bin	*bin;
	int		type;
	int		index;

	if (list == NULL && m_error(20))
		return (NULL);
	index = 0;
	if (check_com_for_bintree(list) != 0 ||
	(type = get_next_type(list, &index, ';', 1)) == -1)
	{
		free(list);
		return (NULL);
	}
	if ((bin = (t_bin *)malloc(sizeof(t_bin))) == NULL && error(9))
	{
		free(list);
		return (NULL);
	}
	bin->type = type;
	bin->sub = (type == 0) ? ft_strdup(list) : NULL;
	bin->left = (type == 0) ? NULL : ft_pipe(get_sub(list, index, type, 0));
	bin->right = (type == 0) ? NULL : ft_pipe(get_sub(list, index, type, 1));
	free(list);
	return (bin);
}
