/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:26:30 by csellier          #+#    #+#             */
/*   Updated: 2016/11/28 16:19:39 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		free_tree(t_bin *tree)
{
	if (tree == NULL)
		return (1);
	if (tree->right)
		free_tree(tree->right);
	if (tree->left)
		free_tree(tree->left);
	if (tree->sub != NULL)
		free(tree->sub);
	if (tree)
		free(tree);
	return (1);
}

int		free_ft_env(t_shell *v)
{
	if (v == NULL)
		return (1);
	if (v->environ != NULL)
	{
		freesplit(v->environ);
		free(v->environ);
	}
	if (v->split != NULL)
	{
		freesplit(v->split);
		free(v->split);
	}
	if (v->path != NULL)
	{
		freesplit(v->path);
		free(v->path);
	}
	return (1);
}

int		ft_free_l(t_com *list)
{
	if (list == NULL)
		return (1);
	while (list && list->next)
	{
		list = list->next;
		if (list && list->prev)
			free(list->prev);
	}
	if (list)
		free(list);
	return (1);
}

int		ft_free_h(t_histo *histo)
{
	if (histo == NULL)
		return (1);
	while (histo && histo->next)
	{
		histo = histo->next;
		if (histo->prev)
		{
			ft_free_l(histo->prev->chaine);
			free(histo->prev);
		}
	}
	if (histo)
	{
		ft_free_l(histo->chaine);
		free(histo);
	}
	return (1);
}
