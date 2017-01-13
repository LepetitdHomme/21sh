/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:47:28 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:13:42 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		before(char *com, int i)
{
	int	ret;
	int	dig;

	if (com == NULL)
		return (-1);
	ret = i - 1;
	if (ret < 0 || !com[ret] || ft_isdigit(com[ret]) == 0)
		return (i);
	dig = ret;
	while (dig >= 0 && com[dig])
	{
		if (com[dig] == ' ')
			return (dig < i ? dig + 1 : i);
		else if (ft_isdigit(com[dig]) == 0)
			return (i);
		dig--;
	}
	return (dig < i ? dig + 1 : i);
}

static int		esperluette(char *com, int i)
{
	int len;

	if (com == NULL)
		return (-1);
	len = (int)ft_strlen(com);
	i++;
	if (i < len && com[i] == '-')
		return (i);
	while (i < len && com[i])
	{
		if (is_quote(com[i]) != -1)
			i = end_of_quote(com, i);
		if (com[i] == ' ' || is_redir(com[i]) != -1)
			return (i - 1);
		i++;
	}
	return (i - 1);
}

static int		after(char *com, int i)
{
	int	ret;
	int	len;

	if (com == NULL)
		return (-1);
	len = (int)ft_strlen(com);
	ret = i + 1;
	if (ret < len && is_redir(com[ret]) != -1)
		ret++;
	if (ret < len && com[ret] && com[ret] == '&')
		return (esperluette(com, ret));
	while (ret < len && com[ret] == ' ')
		ret++;
	while (ret < len)
	{
		if (is_quote(com[ret]) != -1)
			ret = end_of_quote(com, ret);
		if (com[ret] == ' ' || is_redir(com[ret]) != -1)
			break ;
		ret++;
	}
	return (ret - 1);
}

static char		*isolate_redir(t_shell *shell, char *ret, int i)
{
	int	a;
	int	z;

	if (shell == NULL)
		return (NULL);
	if ((a = before(ret, i)) == -1)
		return (NULL);
	if ((z = after(ret, i)) == -1)
		return (NULL);
	if (save_redir(shell, a, z, ret) == -1 && error(18))
		return (NULL);
	return (less_redir(ret, a, z));
}

char			*handle_redir(t_shell *shell, char *command)
{
	int		i;
	char	*ret;

	i = 0;
	if ((shell == NULL || command == NULL) && error(0))
		return (NULL);
	if (redir_is_first(command) == 1 && m_error(18))
		return (NULL);
	if ((ret = ft_strdup(command)) == NULL && error(0))
		return (NULL);
	while (ret && ret[i])
	{
		if (is_quote(ret[i]) != -1)
			i = end_of_quote(ret, i);
		else if (is_redir(ret[i]) == 1 && check_redir(ret, i) != -1)
		{
			ret = isolate_redir(shell, ret, i);
			i = -1;
		}
		if (i == -1 || ret[i])
			i++;
	}
	return (ret);
}
