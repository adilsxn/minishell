/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:14:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 18:37:15 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define HD_W "warning: here-document delimited by end-of-file"
# define HD_FILE "/tmp/heredoc"

# define ERROR -1
// lexer
typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	TWORD,
}					t_token;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_env
{
	const char		*key;
	const char		*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_envy
{
	char			*str2;
	char			*str3;
	char			*tmp;
	int				i;
	t_env			*env2;
	int				len;
}					t_envy;

// parser
typedef enum e_rdirkind
{
	RDR_OUT,
	RDR_IN,
	RDR_APP,
	RDR_HD,
	RDR_CNT,
}					t_rdirkind;

typedef struct s_rdr
{
	t_rdirkind		kind;
	char			*value;
	struct s_rdr	*next;	t_lexer	*lex;

}					t_rdr;

typedef struct s_cmd
{
	char			*path;
	int				argc;
	char			**args;
	char			**envp;
	t_rdr			*rdir;
}					t_cmd;

typedef struct s_ppe
{
	int				pid;
	int				exit_code;
	t_cmd			*cmd;
	struct s_ppe	*prev;
	struct s_ppe	*next;
}					t_ppe;

typedef struct s_tool
{
	char			*arg;
	t_lexer			*lexer;
	t_ppe			*pipes;
	t_env			*env;
	char			**envp;
}					t_tool;

extern int			g_last_ret_code;

int					init_env(char **envp, t_env **env);
t_env	*mk_env(const char *key, const char *value, t_env *prev);
t_env				*set_env(t_env **env, const char *key, const char *value);
int					unset_env(t_env *env, const char *key);
t_env				*get_env(t_env *env, const char *key);
// int traverse_msh_env(t_msh_envlist *list);
int					del_env(t_env *env);

// bi
typedef int			t_bi(char **args, t_tool *data);
int					msh_cd(char **args, t_tool *data);
int					msh_echo(char **args, t_tool *data);
int					msh_env(char **args, t_tool *data);
int					msh_exit(char **args, t_tool *data);
int					msh_export(char **args, t_tool *data);
int					msh_pwd(char **args, t_tool *data);
int					msh_unset(char **args, t_tool *data);

// lexer
int					ft_isspace(int c);
int					count_spaces(char *str, int i);
int					new_node(char *str, int token, t_lexer **lexer_list);
int					len_quote(int i, char *str, char quote);
t_token				check_token(int c1, int c2);
int					len_word(int i, char *str, t_lexer **lexer_list);
char				*del_quotes(char *str, char c);
t_lexer				*lexer(char *str, t_lexer *lexer);

void				*clear_one(t_lexer **lst);
void				del_first(t_lexer **lst);
void				del_one(t_lexer **lst, int i);
void				lst_clear(t_lexer **lst);
// int					ft_error(int error, t_tool *tool);

// parser
bool				is_builtin(char *str);
void				free_arr(char **arr);
void				ft_free(void *ptr);
void				ft_err(char *message, char *detail);
void				free_rdr(t_rdr *rdir);
t_rdr				*build_rdr(t_lexer *lexi);
void				free_cmd(t_cmd *cmd);
t_cmd				*mk_cmd(t_tool *data);
t_ppe				*parser(t_tool *data);
void				free_pipe(t_ppe *pipe);
int					heredoc(t_lexer *lexi);

// expander

char				*del_quote(char *str, char c);
char				*get_key(char *str);
int					envy(t_env **env2, t_env *env, char **str3, char *tmp);
char				*double_strj(char *str2, char *str3, char *str1);
char				*tmpcheck(char **tmp, char **str1, int i);
void				checker(t_env *env2, char **str2, int i);
char				*expander_help1(int len, char *str2, char **str1, int i);
char				**ft_arrdup(char **arr);
void				loop_help2(int *i, char **str2, char *str3, char **str1);
t_lexer				*expander2(t_env *env, t_lexer *lexi);
char				**ft_split2(char const *s, char c);
char				*init_expand(char **str, char ***str1);
char				*expander(t_env *env, char *str1);
void				free_array(char **array);
void				freer(t_envy *ex, char *str);

// minishell loop
int					count_token(t_lexer *lexi);
char				**build_av(t_lexer *lexi);
char				*cmd_finder(t_tool *data, char *cmd);
void				exec_cmd(t_tool *data);
t_bi				*get_bi(char *cmd);
int					exec_bi(t_cmd *cmd, t_tool *data);
void				exec_bin(t_cmd *cmd);
int					exec_rdr(t_rdr *rdr);
void				exec_pipe(t_tool *data);

// cleanup
void				clean_data(t_tool *data, bool has_history);
void				clean_fds(void);
int					sub(char *str, int i, int count, t_lexer **lexer);
// signal
void				sig_handl(void);

#endif
