/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_complete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:31:00 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:28:17 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static struct dirent	*find_stream(DIR *dir, char *word, t_com **l, t_com **n)
{
	struct dirent	*s;

	if (dir == NULL || word == NULL)
		return (NULL);
	while ((s = readdir(dir)) != NULL)
	{
		if (ft_strcmp(s->d_name, "..") != 0 && ft_strcmp(s->d_name, ".") != 0 &&
		ft_strncmp(s->d_name, word, ft_strlen(word)) == 0)
		break;
	}
	if (ft_strlen(word) == ft_strlen(s->d_name))
	{
		closedir(dir);
		return (NULL);
	}
	while (*l && (*l)->u != 1)
		*l = (*l)->next;
	*n = (t_com *)malloc(sizeof(t_com));
	(*n)->c = s->d_name[ft_strlen(word)];
	(*n)->u = 0;
	(*n)->h = 0;
	(*n)->prev = (*l)->prev;
	(*l)->prev->next = *n;
	return (s);
}

static int				complete(DIR *dir, char *word, t_com *l)
{
	struct dirent	*s;
	t_com			*new;
	size_t			i;

	if (dir == NULL || word == NULL || l == NULL ||
	(s = find_stream(dir, word, &l, &new)) == NULL)
		return (1);
	i = ft_strlen(word);
	while (s->d_name[++i])
	{
		new->next = malloc(sizeof(t_com));
		new->next->c = s->d_name[i];
		new->next->u = 0;
		new->next->h = 0;
		new->next->prev = new;
		new = new->next;
	}
	new->next = l;
	l->prev = new;
	closedir(dir);
	return (1);
}

static int				display_complete3(DIR *dir, char *word, size_t len)
{
	struct dirent	*s;
	int				i;
	int				tot;

	if (!(get_buf(NULL)) || get_buf(NULL)->w_col <= (int)len || dir == NULL)
		return (1);
	tot = 0;
	ft_putchar_fd('\n', get_env(NULL)->fd);
	while ((s = readdir(dir)) != NULL)
	{
		if (ft_strcmp(s->d_name, "..") == 0 || ft_strcmp(s->d_name, ".") == 0 ||
		ft_strncmp(s->d_name, word, ft_strlen(word)) != 0)
			continue;
		if ((int)(tot + len + 1) > get_buf(NULL)->w_col)
		{
			ft_putchar_fd('\n', get_env(NULL)->fd);
			tot = 0;
		}
		ft_putstr_fd(s->d_name, get_env(NULL)->fd);
		i = 0;
		while (ft_strlen(s->d_name) + (i++) <= len)
			ft_putchar_fd(' ', get_env(NULL)->fd);
		tot += len + 1;
	}
	return (1);
}

static int				display_c2(DIR *dir, char *word, int count, size_t len)
{
	char	answer;

	if (dir == NULL || word == NULL)
		return (error(0));
	answer = 0;
	if (count >= 10)
	{
		ft_putchar_fd('\n', get_env(NULL)->fd);
		ft_putstr_fd("Display all ", get_env(NULL)->fd);
		ft_putnbr_fd(count, get_env(NULL)->fd);
		ft_putstr_fd(" possibilities ? (y or n)", get_env(NULL)->fd);
		while (answer != 121 && answer != 110)
		{
			answer = 0;
			read(get_stdin(-1), &answer, 4);
		}
	}
	if (count < 10 || answer == 121)
		display_complete3(dir, word, len);
	closedir(dir);
	ft_putchar_fd('\n', get_env(NULL)->fd);
	affich_prompt(get_env(NULL));
	return (1);
}

int						display_complete(DIR *dir, char *word, t_com **l, int i)
{
	struct dirent	*stream;
	int				count;
	size_t			len;

	if (dir == NULL || word == NULL || l == NULL)
		return (error(0));
	len = 0;
	count = 0;
	while ((stream = readdir(dir)) != NULL)
	{
		if (ft_strcmp(stream->d_name, "..") == 0 ||
		ft_strcmp(stream->d_name, ".") == 0 ||
		ft_strncmp(stream->d_name, word, ft_strlen(word)) != 0)
			continue;
		count++;
		len = ft_strlen(stream->d_name) > len ? ft_strlen(stream->d_name) : len;
	}
	closedir(dir);
	if (count == 1)
		return (complete(get_stream(i), word, *l));
	if (count > 1)
		return (display_c2(get_stream(i), word, count, len));
	return (1);
}
