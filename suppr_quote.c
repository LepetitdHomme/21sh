/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:32:28 by csellier          #+#    #+#             */
/*   Updated: 2016/12/01 21:11:59 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		count_quote(char *quotefull, int i)
{
	int ret;
	int	j;

	if (quotefull == NULL)
		return (0);
	ret = 0;
	j = 0;
	while (quotefull[i] != '\0')
	{
		if (is_quote(quotefull[i]) != -1)
		{
			if ((j = end_of_quote(quotefull, i)) != i)
			{
				ret += 2;
				i = j;
			}
		}
		i++;
	}
	return (ret);
}

int		quoteless(char **q, int i, int j, int l)
{
	char	*new;
	int		k;

	new = NULL;
	if (q == NULL || *q == NULL || ((new = (char *)malloc(sizeof(char) *
	(ft_strlen(*q) - count_quote(*q, i) + 1))) == NULL && error(9)))
		return (1);
	k = 0;
	while ((*q)[l] != '\0')
	{
		if (is_quote((*q)[l]) != -1)
		{
			j = end_of_quote(*q, l);
			l++;
			while (l < j)
				new[k++] = (*q)[l++];
			l++;
		}
		else
			new[k++] = (*q)[l++];
	}
	new[k] = '\0';
	free(*q);
	*q = new;
	return (1);
}
