/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 11:51:09 by csellier          #+#    #+#             */
/*   Updated: 2017/03/13 17:17:15 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			free_redir(t_shell *v)
{
	t_redir *vag;

	if (v->redir == NULL)
		return (1);
	vag = v->redir;
	while (vag && vag->next)
	{
		vag = vag->next;
		if (vag && vag->prev && vag->prev->redir)
			free(vag->prev->redir);
		if (vag && vag->prev)
			free(vag->prev);
	}
	if (vag && vag->redir)
		free(vag->redir);
	if (vag)
		free(vag);
	v->redir = NULL;
	return (1);
}

static int	free_mini2(t_shell shell)
{
	if (shell.split != NULL)
	{
		freesplit(shell.split);
		free(shell.split);
		shell.split = NULL;
	}
	if (shell.path != NULL)
	{
		freesplit(shell.path);
		free(shell.path);
	}
	return (1);
}

int			free_mini(t_shell shell, t_env *v)
{
	if (v == NULL)
		return (error(0));
	if (v->env != NULL)
	{
		freesplit(v->env);
		free(v->env);
		v->env = NULL;
	}
	if (shell.environ != NULL)
	{
		v->env = copy_split(shell.environ);
		freesplit(shell.environ);
		free(shell.environ);
		shell.environ = NULL;
	}
	if (v->c_histo != NULL)
		ft_free_h(v->c_histo);
	v->c_histo = NULL;
	free_mini2(shell);
	return (1);
}

int			refresh_histo(t_env *env, t_histo *copy)
{
	if (env == NULL || copy == NULL)
		return (error(0));
	if (env->c_histo != NULL)
		ft_free_h(env->c_histo);
	env->c_histo = copy;
	return (1);
}

int			free_main(t_env env)
{
	char	*prompt;

	if (env.env == NULL)
		return (error(0));
	freesplit(env.env);
	free(env.env);
	env.env = NULL;
	if ((prompt = get_prompt(NULL)) != NULL)
		free(prompt);
	return (1);
}
