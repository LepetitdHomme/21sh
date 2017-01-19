/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:34:49 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:38:31 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			check_builtin(t_shell *shell, char *command, int forked)
{
	char	*post_redir;

	if (shell == NULL || command == NULL)
		return (-1);
	shell->command = NULL;
	post_redir = NULL;
	if ((post_redir = handle_redir(shell, command)) == NULL)
		return (0);
	specialchar(shell, &post_redir);
	if (quoteless(&post_redir, 0, 0, 0) != 1)
		return (-1);
	if ((shell->split = ft_strsplit(post_redir, ' ')) == NULL)
		return (m_error(1));
	free(post_redir);
	if ((count_split(shell->split) < 1 && m_error(18)) ||
	((forked = treat_redir(shell)) == -1 && m_error(17)))
		return (1);
	if (shell->split[0] == NULL || (forked != 1 && exe_command(shell) == -1))
		return (1);
	freesplit(shell->split);
	free(shell->split);
	shell->split = NULL;
	free_redir(shell);
	return (0);
}

int			search_path(t_shell *shell, char **environ)
{
	int i;

	i = 0;
	if (shell == NULL || environ == NULL)
		return (-1);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	shell->path = NULL;
	return (-1);
}

int			init_struct(t_shell *shell, char **split, char **environ)
{
	if (shell == NULL)
		return (-1);
	shell->environ = ft_copy_split(environ);
	shell->split = split;
	shell->prompt = NULL;
	shell->path = NULL;
	shell->redir = NULL;
	ft_init_path(shell);
	return (1);
}

int			mini(t_env *v, t_com **list, t_com *cp, t_term *buf)
{
	t_shell	shell;
	t_bin	*bin;

	if (v == NULL || list == NULL || *list == NULL || cp == NULL)
		return (-1);
	shell.argc = 0;
	shell.argv = NULL;
	mini_clear(*list);
	ft_putchar_fd('\n', get_fd(v->fd));
	buf->count_cr = 0;
	if (init_struct(&shell, NULL, v->env) == -1)
		return (-1);
	set_terme(&get_env(NULL)->term);
	tputs(tgetstr("ve", NULL), 0, ft_out);
	get_static_fork(0);
	bin = ft_pipe(list2str(*list));
	lecture(&shell, bin);
	free_tree(bin);
	mode_canonique(get_env(NULL)->term);
	tputs(tgetstr("vi", NULL), 0, ft_out);
	save_line(v, *list);
	free_mini(shell, v);
	ft_putchar_fd('\n', v->fd);
	affich_prompt(v);
	return (1);
}
