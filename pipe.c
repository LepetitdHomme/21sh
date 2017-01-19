/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 14:40:06 by csellier          #+#    #+#             */
/*   Updated: 2016/12/05 15:23:19 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Mallocs a binary tree of commands
** and organizes it by looking for bash operators
*/

#include "ft_21sh.h"

static int		operators(char *list, int i)
{
	int	quote;

	quote = -1;
	while (list && list[i])
	{
		if ((quote = is_quote((list[i]))) != -1)
			i = (end_of_quote(list, i));
		else if (list[i] == ';')
			return (i);
		i++;
	}
	i = 0;
	quote = -1;
	while (list && list[i])
	{
		if ((quote = is_quote((list[i]))) != -1)
			i = (end_of_quote(list, i));
		else if (list[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}

static t_bin	*operator_2(char **sub, t_bin *bin, char *list)
{
	int	i;

	if (list == NULL)
		return (NULL);
	i = operators(list, 0);
	if (i != -1 && list[i] == '|')
	{
		if ((is_operande(list, i) == -1 && m_error(20)) ||
		((*sub = ft_strsub(list, 0, i)) == NULL && error(9)))
		{
			free(list);
			free(bin);
			return (NULL);
		}
		bin->type = 2;
		bin->sub = NULL;
		bin->left = ft_pipe(*sub);
		bin->right = ft_pipe(ft_strsub(list, i + 1, ft_strlen(list) - i));
		free(list);
		return (bin);
	}
	return (NULL);
}

static t_bin	*operator_1(char **sub, t_bin *bin, char *list)
{
	int i;

	i = operators(list, 0);
	if (i != -1 && list[i] != -1 && list[i] == ';')
	{
		if ((is_operande(list, i) == -1 && m_error(20)) ||
		((*sub = ft_strsub(list, 0, i)) == NULL && error(9)))
		{
			free(list);
			free(bin);
			return (NULL);
		}
		bin->type = 1;
		bin->sub = NULL;
		bin->left = ft_pipe(*sub);
		bin->right = ft_pipe(ft_strsub(list, i + 1, ft_strlen(list) - i));
		free(list);
		return (bin);
	}
	else
		return (operator_2(sub, bin, list));
}

t_bin			*ft_pipe(char *list)
{
	t_bin	*bin;
	char	*sub;
	int		i;

	if (list == NULL && error(0))
		return (NULL);
	if ((bin = (t_bin *)malloc(sizeof(t_bin))) == NULL && error(9))
		return (NULL);
	if ((i = operators(list, 0)) == -1)
	{
		bin->type = 0;
		bin->sub = ft_strdup(list);
		free(list);
		bin->left = NULL;
		bin->right = NULL;
		return (bin);
	}
	return (operator_1(&sub, bin, list));
}
