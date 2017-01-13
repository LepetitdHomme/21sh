/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:31:00 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:28:17 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		get_index(t_com *l)
{
	int	ret;

	ret = 0;
	if (l == NULL)
		return (error(0));
	while (l && l->u != 1)
	{
		l = l->next;
		ret++;
	}
	if (l && l->c != ' ')
		return (ret);
	return (-1);
}

DIR				*get_stream(int x)
{
	DIR	*b;

	if (x == 1)
		return ((b = opendir("/bin")));
	return ((b = opendir(".")));
}

static char		*find_word(t_com *l)
{
	if (l == NULL && error(0))
		return (NULL);
	while (l && l->u != 1)
		l = l->next;
	while (l->prev && l->prev->c != ' ')
		l = l->prev;
	return (list2str_tabu(l));
}

int				tabu(t_env *env, t_term *b, t_com **l)
{
	int		ret;
	char	*str;
	char	*word;
	int		index;

	if (env == NULL || b == NULL || l == NULL || *l == NULL)
		return (error(0));
	if ((*l && (*l)->c == -1) || b->buf[0] != 9 || (str = list2str(*l)) == NULL)
		return (-1);
	if ((index = get_index(*l)) == -1)
		return(-1);
	if ((word = find_word(*l)) == NULL)
		return (-1);
	ret = -1;
	if (ft_strchri(str, ' ') != -1 && ft_strchri(str, ' ') < index)
		ret = display_complete(get_stream(0), word, l, 0);
	else
		ret = display_complete(get_stream(1), word, l, 1);
	free(str);
	free(word);
	return (ret);
}
