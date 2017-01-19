/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:53:32 by csellier          #+#    #+#             */
/*   Updated: 2016/12/09 17:53:35 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "libft/libft.h"
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>

#include <stdio.h>
#define DEBUG printf("%s, %d\n", __FILE__, __LINE__)

# define ROUGE "\033[1;31m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define END "\033[0;m"
# define WHITE "\033[1;35m"

typedef struct		s_com
{
	int				c;
	int				u;
	int				h;
	struct s_com	*prev;
	struct s_com	*next;
}					t_com;

typedef struct		s_histo
{
	t_com			*chaine;
	int				affich;
	struct s_histo	*next;
	struct s_histo	*prev;
}					t_histo;

typedef struct		s_env
{
	int				argc;
	char			**argv;
	char			**env;
	struct termios	term;
	int				fd;
	int				missin_q;
	t_com			*begin;
	t_histo			*histo;
	t_histo			*c_histo;
}					t_env;

typedef struct		s_term
{
	char			buf[8];
	t_com			*pp;
	int				maj;
	int				w_col;
	int				w_row;
	int				count_cr;
	char			*cd;
	char			*cl;
	char			*cr;
	char			*mr;
	char			*me;
	char			*le;
	char			*nd;
	char			*up;
	char			*ho;
	char			*vi;
	char			*ve;
}					t_term;

typedef struct		s_redir
{
	char			*redir;
	int				type;
	struct s_redir	*next;
	struct s_redir	*prev;
}					t_redir;

typedef struct		s_shell
{
	char			**command;
	char			**split;
	int				argc;
	char			**argv;
	char			**environ;
	char			**path;
	char			*prompt;
	t_redir			*redir;
}					t_shell;

typedef struct		s_bin
{
	int				type;
	struct s_bin	*left;
	struct s_bin	*right;
	char			*sub;
}					t_bin;

/*
** Minishell
*/

int					ft_echo(t_shell *shell);
int					specialchar(t_shell *shell, char **command);
int					heredoc(t_redir *redir, int i);
int					quoteless(char **quotefull, int i, int j, int k);

char				*less_redir(char *com, int a, int b);
int					save_redir(t_shell *shell, int a, int b, char *com);
int					check_redir(char *s, int i);
int					treat_redir(t_shell *shell);
int					open_file(t_redir *redir, int i, int *fd);
int					fork_redir(int *fd, t_shell *shell);

int					is_redir(char c);
char				*handle_redir(t_shell *shell, char *command);

t_bin				*ft_pipe(char *list);
int					get_static_fork(int i);
int					lecture(t_shell *shell, t_bin *bin);

int					ft_unset_env(char **split, t_shell *shell, int i);
int					m_error(int i);
int					ft_count(char **split);
char				**ft_copy_split(char **split);
int					ft_access(char *path);
int					ft_init_path(t_shell *shell);
int					ft_init_environ(t_shell *shell);
int					struct_show_env(t_shell *v2, char **v1, char **envv1);

int					exist(t_shell *shell, int k, char *value);
int					doesnt(t_shell *shell, char *name, char *value);
int					ft_setenv(t_shell *shell, char *name, char *value, int w);
int					ft_export(t_shell *shell);

int					cd(t_shell *sh);
int					as_path(t_shell *sh, char *curpath);
int					treat_pwd(t_shell *sh);
char				*get_old(t_shell *sh);
int					join_old_and_path(t_shell *sh, char *path, int old);
int					set_old(t_shell *sh);
int					set_pwd(t_shell *sh, int p_flag, char *curpath);
int					as_old(t_shell *sh, char **curpath);
int					set_curpath(char **curpath, char *src, int i);
int					index_directory(char **split);
int					physical_flag(t_shell *sh);

int					check_param(t_shell *shell, int i);
int					display_env(char **split);
int					ft_env(t_shell *shell);

int					is_a_builtin(t_shell *shell);

int					freesplit(char **split);
int					which_bin(t_shell *shell);
int					mowgli(char *path, t_shell *shell);
int					exe_command(t_shell *shell);

int					display_prompt(t_shell *shell);

void				ft_sigwinch(int s);
void				ft_all_sig(void);
void				ft_signal_3(int echo);
void				ft_signal_2(int echo);
void				ft_signal(int echo);
int					check_builtin(t_shell *shell, char *command, int forked);
int					search_path(t_shell *shell, char **environ);
int					init_struct(t_shell *shell, char **split, char **env);

/*
** 21SH
*/

int					reset_affich_histo(t_env *v);
int					set_prompt_for_reverse(t_env *v, t_term *b, int i);
int					check_reverse(t_env *v, t_com **l);
int					get_reverse(int x);
int					find_in_histo(t_env *v, t_com *l);
int					display_reverse(t_env *v, t_term *b);
int					get_histo_r(int x);
int					ctrlr(t_env *v, t_term *b, t_com **l, int i);

DIR					*get_stream(int x);
int					display_complete(DIR *dir, char *word, t_com **l, int i);
int					tabu(t_env *v, t_term *b, t_com **l);
int					free_redir(t_shell *v);
int					free_tree(t_bin *tree);
int					free_mini(t_shell shell, t_env *env);
t_com				*newcom(void);
int					index_pwd(char **env, char *cmp);
int					ft_coller_tool(t_com **vag, t_com **tmp, t_com **list);
int					get_stdin(int fd);


int					tilde(t_shell *sh, char **com, int i, int j);

int					free_main(t_env env);
int					refresh_histo(t_env *env, t_histo *copy);

/*
** COPY_LST.C
*/

int					concat_lst(t_env *v, t_com *list);
t_com				*copy_lst(t_com *list);

int					printable(t_env *v, t_term *b, t_com **list);
int					non_printable(t_env *v, t_term *b, t_com **list, int ret);

char				*list2str_tabu(t_com *list);
char				*list2str(t_com *list);
int					count_o(t_com *list);
char				*get_prompt(char *prompt);
int					quotes(t_env *v, t_term *b, t_com **list);
int					parse_quote(t_env *v, t_com **list, int first);
int					if_missing_quote(t_env *v, t_com **list);
int					missing_quote(t_com *list, int ok);
int					ask_for_quote(t_env *v, int quote);
int					suppr_quote(t_com **list, t_com *quote);
int					is_quote(int c);
void				quote_priority(int *ok, t_com **list);
int					check_subsh(int *ok, t_com **list);
int					end_of_quote(char *list, int i);
int					til_end_of_quote(t_com **list);
int					fermant(int i, int c);

/*
** HISTO.C
*/

int					c_histo_b(t_env *env);
int					copy_histo(t_env *env);
int					copy_list(t_histo *locate, t_com *src);
t_histo				*which_list(t_env *env);
int					save_line(t_env *env, t_com *l);

/*
** AFFICH.C
*/

int					affich_curs(t_com *list, t_com *init, t_term *buf, int i);
int					ft_out(int c);
int					affich_prompt(t_env *env);
int					display(t_env *env, t_term *buf, t_com *list);

int					get_fork(int i);
int					count_histo(t_histo *list);
int					count_u(t_com *list);
int					get_fd(int fd);
int					delete_t_com(t_com **list);
t_term				*get_buf(t_term *buf);
t_com				**get_list(t_com **list);
int					suppr_list(t_env *cp, t_com **list);
t_com				*new_com(t_com *cp);
t_env				*get_env(t_env *env);
int					get_term_size(t_env *env);

/*
** SET.C
*/

int					set_buf(t_term *buf);
int					set_terme(struct termios *term);
int					set_list(t_com **list);
int					set_histo(t_env *env, t_com *l);
int					set_env(t_env *env, int argc, char **argv, char **v);

int					xcv(t_env *v, t_term *b, t_com **list);
int					home_end(t_term *buf, t_com *list);
int					ft_delete(t_env *env, t_term *buf, t_com **list);
int					shift(t_env *v, t_term *buf, t_com *list);
int					control(t_env *v, t_term *buf, t_com *l);
int					is_operande(char *list, int i);
int					redir_is_first(char *list);
int					arow(t_env *env, t_term *buf, t_com *l);

int					mode_canonique(struct termios term);
int					mini(t_env *v, t_com **list, t_com *cp, t_term *buf);
int					mini_clear(t_com *com);
int					treat(t_env *env, t_term *buf, t_com **list);

int					free_ft_env(t_shell *v);
int					ft_free_h(t_histo *histo);
int					ft_free_l(t_com *list);
int					error(int index);
void				super_exit(void);

#endif
