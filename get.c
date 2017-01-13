/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 09:50:56 by csellier          #+#    #+#             */
/*   Updated: 2016/11/27 12:08:33 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
