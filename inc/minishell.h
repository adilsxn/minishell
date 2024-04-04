/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:14:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/04/04 15:06:48 by matde-je         ###   ########.fr       */
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
# define HD_FILE "/tmp/heredoc_"

# define ERROR -3
// lexer
typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}					t_token;

typedef struct s_lexer
{
	char			*str;
    char			*str2;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_env1
{
	char			*str2;
	char			*str3;
	char			*tmp;
	int				i;
	struct s_env	*env2;
	int				len;
}					t_env1;

typedef struct s_var
{
	char			*str;
	int				i;
	int				count;
}					t_var;

typedef struct s_env
{
	char			*key;
	char			*value;
	t_env1			*env1;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_rdr
{
	t_token			type;
	char			*value;
    char			*value2;
	int				fd;
	struct s_rdr	*next;
}					t_rdr;

typedef struct s_cmd
{
	char			*path;
	int				argc;
	char			**args;
	t_rdr			*rdir;
	bool			io;
	bool			path_on;
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
	bool			ninter;
	t_var			*var;
}					t_tool;

extern volatile int	g_last_ret_code;

t_env				*init_env(char **envp);
bool				valid_key(char *key);
t_env				*mk_env(const char *key, const char *value, t_env *prev);
t_env				*set_env(t_env **env, const char *key, const char *value);
int					unset_env(t_env **env, const char *key);
t_env				*env_iter(t_env *env, const char *key);
char				*get_env(t_env *env, const char *key);
int					del_env(t_env *env);
// bi
typedef int			t_bi(char **args, t_tool *data);
int					msh_cd(char **args, t_tool *data);
int					msh_echo(char **args, t_tool *data);
int					msh_void(char **args, t_tool *data);
int					msh_env(char **args, t_tool *data);
int					msh_exit(char **args, t_tool *data);
int					msh_export(char **args, t_tool *data);
int					msh_pwd(char **args, t_tool *data);
int					msh_unset(char **args, t_tool *data);

void				printin(t_lexer *lex);
// lexer
int					ft_isspace(int c);
int					count_spaces(char *str, int i);
int					new_node(char *str, int token, t_lexer **lexer_list);
int					len_quote(int i, char *str, char quote);
t_token				che_tok(int c1, int c2);
int					len_word(int i, char *str, t_lexer **lexer_list,
						t_tool *tool);
char				*del_quote(char *str, char c);
t_lexer				*lexer(char *str, t_lexer *lexer, t_tool *tool);
void				lexer_redux(t_lexer **lexer);
t_lexer				*begin_end(t_lexer *lexer);
int					sub(t_var *var, t_lexer **lexer);
int					token_help(int i, char *str, int *trig, t_lexer **lex);
void				lex_del(t_lexer **lexer, int i, int j);
void				lst_clear(t_lexer **lst);
int					lex_check_again(t_lexer *lex);
int					reti(int trig);
int					quote_assist(char *str, int q);
void				quote_help(t_lexer *shell);
char				*syntax_error(int i);
int					err_special_char(t_lexer *lex, int i);
void				del_one(t_lexer **lst, int i);
void				renumber(t_lexer **lst);
// parser
bool				is_builtin(char *str);
void				free_arr(char **arr);
void				ft_free(void **ptr);
void				ft_err(char *message, char *detail, char *errorstr,
						int ret_code);
void				free_rdr(t_rdr **rdir);
t_rdr				*build_rdr(t_lexer *lexi, t_cmd *cmd);
void				free_cmd(t_cmd **cmd);
t_cmd				*mk_cmd(t_lexer *lexer, t_env *env);
int					has_pipe(t_lexer *lexer);
t_ppe				*parser(t_tool *data);
void				free_pipe(t_ppe **pipe);
int					handle_input(t_rdr *rdr);
int					handle_append(t_rdr *rdr);
int					handle_output(t_rdr *rdr);
bool				has_heredoc(t_lexer *lexer);
bool				name_heredoc_file(t_lexer *lexer);
bool				delim_has_quotes(char *str);
int					handle_heredoc(t_rdr *rdr);
void				parse_heredoc(t_lexer *lexer, t_env *env);

// expander
char				*get_key(char *str);
int					env1_func(t_env **env2, t_env *env, char **str3, char *tmp);
char				*tmpcheck(char **tmp, char **str1, int i);
void				checker(t_env1 *env1, int j, char **str1);
char				*expander_help1(int len, char **str2, char **str1, int i);
void				loop_help2(t_env1 **ex, char **str2, char *str3,
						char **str1);
t_lexer				*expander2(t_env *env, t_lexer *lexi);
char				**ft_split2(char const *s, char c);
char				*init_expand(char **str, char ***str1);
char				*expander(t_env *env, char *str1);
void				free_array(char **array);
char				*freer(t_env1 **ex, char *str, char **str1);

// minishell loop
int					count_token(t_lexer *lexi);
char				**build_av(t_lexer *lexi, int tkn_nbr);
char				*cmd_finder(t_env *env, char *cmd);
int					cmd_error(t_cmd *cmd);
void				exec_cmd(t_tool *data);
t_bi				*get_bi(char *cmd);
int					exec_bi(t_cmd *cmd, t_tool *data);
void				get_exit_code(int wstatus);
void				exec_bin(t_cmd *cmd);
int					exec_rdr(t_rdr *rdr);
void				exec_pipe(t_tool *data);

// cleanup
void				clean_data(t_tool *data, bool has_history);
void				ft_close(int fd);
void				clean_fds(void);

// signal
void				signal_handler(void (*handler)(int), int signal);
void				sig_new_prompt(int sig);
void				sig_hdoc_child(int sig);
void				sig_hdoc_parent(int sig);

#endif
