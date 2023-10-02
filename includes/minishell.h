/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:36:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/02 06:53:12 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"
// # include "../ft_printf/ft_printf.h"
# define SYNTAXERROR "bash: syntax error near unexpected token `|'\n"

typedef struct t_data {
	int				nbcmd;
	int				fd[2];
	int				prev_pipe;
	char			**env;
	char			**path;
	int				*pid;
	int				exit_code;
	char			**arg;
	char			**split;
	char			*str;
	int				n_hrdocs;
	struct t_cmd	*cmds;
	struct t_hrdoc	*hrdoc;
}		t_data;

typedef struct t_cmd {
	char			*cmd;
	char			**arg;
	int				*type;
	char			**file;
	struct t_data	*data;
}		t_cmd;

typedef struct t_hrdoc {
	int		fd[2];
	char	*key;
	int		size;
}		t_hrdoc;

/*		PAOLARSING	*/
/*		QUOTE		*/
void		ft_quote(char *str);
void		ft_unquote(char **tab, char ***env);

/*		SYNTAX		*/
int			check_quote(char *str);
int			check_rafter(char *str, int i);
int			ft_syntax(char *str);
int			syntax(t_data *data, char *str);

/*		AMBIGUOUS REDIRECT		*/
int			ft_ar(char *str);

/*		SPACE		*/
int			skip_isspace(char *str, int i);
char		*ft_space(char *input);
int			skip_quote(char *str, int i);
int			dquote_expand(char **str, int e);

/*		SIGNALS		*/
void		allsignals(void);
//static void	sigint_heredoc(int signum);

/*		EXPAND		*/
int			replace_utils(char **str, char *new, char *replace, int start);
int			expand_delimit(char *str, int start);
int			end_of_expand(char **str, int start);
int			ft_expand(char **str, char ***env, int status);

/*		ENV		*/
char		**ft_copy(char **env);
int			ft_env(char **env);
char		*return_value(char *str);

/*		ECHO		*/
int			ft_echo(char **tab);

/*		EXPORT		*/
int			replace_in_env(char *add, char ***env);
int			ft_add_to_env(char *str, char ***env);
int			ft_export(char	**str, char ***env, t_data *data);

/*		UNSET		*/
void		ft_remove_from_env(char *str, char ***env);
int			ft_unset(char **tab, char ***env);

/*		CD		*/
int			ft_cd(char **tab, t_data *data);

/*		EXIT		*/
void		num_required(const char *nptr, t_data *data, t_cmd *cmds);
void		two_arg_exit(char **tab, t_data *data, t_cmd *cmds, int i);
void		three_arg_exit(char **tab, t_data *data, t_cmd *cmds, int i);
int			ft_exit(char **tab, t_data *data, t_cmd *cmds);

/*		FREE		*/
void		free_cmd(t_cmd *cmds);
void		free_inchildprocess(t_data *data, t_cmd *cmds, int hd);
void		free_in_fd(t_cmd *cmds);

/*		HERE_DOC		*/
int			how_many_hrdoc(char *str);
char		*key_word(char *s);
void		letsgo_child(t_data *data, t_hrdoc *hrdoc);
void		we_do_fork(t_data *data, t_hrdoc *hrdoc);
void		here_doc(t_data *data, char *str);

/*		PARSE_ARR		*/
int			type_of_arr(char *s);
void		mallocall(t_cmd	*cmds, char **tab);
t_cmd		*parse(char **tab);

/*		PWD				*/
int			how_many_hrdoc(char *str);
int			ft_exit(char **tab, t_data *data, t_cmd *cmds);
int			call_builtin(char *str, t_cmd *cmds, char ***env);
int			builtin(char *str);
int			ft_pwd(void);
int			openfiles_builtin(t_cmd *cmds);
void		here_doc(t_data *data, char *str);

/*		EXEC			*/
char		**get_path(char **env);
char		*find_path(t_data *data, char *cmd);

/*		EXEC PIPEX		*/
void		init(t_data *data, int ac);
int			child_process(t_data *data, char **av, char ***env, int i);
void		parent_process(t_data *data);
void		wait_n_close(t_data *data);
void		execution(t_data *data, char **tab, char ***env);

/*		EXEC ERROR 		*/
void		the_perror(char *str);
void		dup_n_close(int fd1, int fd2);
void		ft_freetab(char **tab);

/*		EXEC UTILS 		*/
void		redirection(t_data *data, t_cmd *cmds, int index);
char		*check_cmd(t_data *data, char ***env, char **tab);
void		free_cmd(t_cmd *cmds);
int			count_len(char **tab);
void		manage_cmds(t_data *data, char ***env);
int			is_there_hrdoc(char *str);

#endif
