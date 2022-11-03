/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:28 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/28 00:07:58 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libraries */
# include "../libft/includes/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

/* ANSI color codes */
# define DEFAULT "\001\033[0;39m\002"
# define RED "\001\033[1;91m\002"
# define BLUE "\001\033[1;94m\002"
# define CYAN "\001\033[1;96m\002"

/* fd[] references from pipe()*/
# define READ_END 0
# define WRITE_END 1

/* Error messages references */
# define QUOTE 1
# define NDIR 2
# define NPERM 3
# define NCMD 6
# define DUPERR 7
# define FORKERR 8
# define PIPERR 9
# define PIPENDERR 10
# define NLERR 11
# define IS_DIR 12
# define NOT_DIR 13

typedef struct s_prompt
{
	t_list	*cmds;
	char	**env;
	pid_t	pid;
}			t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

/* minishell core */
void		*exec_prog(char *input, t_prompt *prompt);
void		*exec_cmd(t_prompt *prompt, t_list *cmd);
int			exec_builtin(t_prompt *prompt, int (*func)(t_prompt *));
/* minishell core utils */
void		*fork_handler(t_prompt *prompt, t_list *cmd, int fd[2]);

/* builtins core */
int			builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int len);
bool		is_builtin(t_mini *n);
/* builtins implemented commands */
int			ft_cd(t_prompt *prompt);
int			ft_pwd(void);
int			ft_echo(t_list *cmd);
int			ft_exit(t_list *cmd, int *is_exit);
/* builtins implemented env  commands */
int			ft_export(t_prompt *prompt);
int			ft_unset(t_prompt *prompt);
/* builtins implemented utils */
int			exit_status_handler(long status);
bool		check_echo_opt(char *opt);
void		join_vars(t_prompt *prompt, char **av, int *i, char *tmp3);
int			var_in_env(char *av, char **env, int i[2]);
bool		parse_var(char *av, char *function_name, int flag);

/* parsing */
char		**ft_input_split(char const *s, char *set);
char		**ft_symsplit(char const *args, char *set);
char		**quotes_trim(char **args);
t_list		*create_list(char **args, int i, t_prompt *p);

/* redirections */
t_mini		*redir_truncate(t_mini *node, char **args, int *i);
t_mini		*redir_append(t_mini *node, char **args, int *i);
t_mini		*redir_input(t_mini *node, char **args, int *i);
t_mini		*redir_heredoc(t_mini *node, char **args, int *i, t_prompt *p);
int			get_here_doc(char *str[2], char *aux[2], t_prompt *p);
/* redirections utils */
int			fd_handler_append(int fd, char *path, struct stat path_stat);
int			fd_handler_truncate(int fd, char *path, struct stat path_stat);

/* prompt and env */
char		*ft_getenv(char *var, char **envp, int n);
char		**ft_setenv(char *var, char *value, char **envp, int n);
t_prompt	init_env(t_prompt prompt, char *str, char **argv);
char		*get_prompt(t_prompt prompt);
char		*expand_vars(char *arg, int i, int quotes[2], t_prompt *prompt);
char		*expand_path(char *arg, int i, int quotes[2], char *var);

/* signals */
void		signal_handler(int sig);

/* utils */
void		*ft_perror(int err_type, char *param, int exit_code);
void		free_content(void *content);

#endif
