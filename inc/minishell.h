/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:14:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/14 23:12:21 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
#include <readline/history.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

# include "../libft/inc/libft.h"

//lexer
typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}t_token;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}t_lexer;


typedef enum e_order {
    MINUS = -1,
    PPE,
    RDR,
    CMD,
} t_order;

typedef struct e_state
{
	char *state;
	int ret_code;
}t_state;

typedef struct s_env
{
	const char *key;
	const char *value;
	struct s_env *prev;
	struct s_env *next;
} t_env;
//parser
typedef struct s_tree
{
    bool   root;
    bool   heredoc;
    char  *token;
    t_order kind;
    void (*fn)(struct s_tree *tree, t_env *env);
    struct s_tree *left;
    struct s_tree *right;
} t_tree;


typedef struct s_tool
{
	char					*arg;
	t_lexer					*lexer;
	t_tree					*tree;
	t_env					*env;
}t_tool;


extern t_state g_state;

int init_env(char **envp, t_env **env);
t_env *set_env(t_env **env, const char *key, const char *value);
int unset_env(t_env *env, const char *key);
t_env *get_env(t_env *env, const char *key);
 // int traverse_msh_env(t_msh_envlist *list);
int del_env(t_env *env);

//bi
int msh_cd(char **args, t_env *env);
int msh_echo(t_tool *tools);
int msh_env(t_tool *tools);
int msh_exit(t_tool *tools);
int msh_export(t_tool *tools);
int msh_pwd(t_tool *tools);
int msh_unset(t_tool *tools);


//lexer
int					is_whitespace(char c);
int					count_spaces(char *str, int i);
int					new_node(char *str, int token, t_lexer **lexer_list);
int					len_quote(int i, char *str, char quote);
t_token				check_token(int c1, int c2);
int					len_word(int i, char *str, t_lexer **lexer_list);

void				*clear_one(t_lexer **lst);
void				del_first(t_lexer **lst);
void				del_one(t_lexer **lst, int i);
void				lst_clear(t_lexer **lst);

//parser
t_tree *make_leaf(t_lexer *lexem);
t_tree *tree_insert(t_tree *tree, t_tree *it);
bool is_complete(t_tree *tree);
t_tree* parser(t_tool *shell);



//expander
size_t				dollar_sign(char *str);
int					after_dollar_len(char *str, int j);
char				*del_quote(char *str, char c);
char				*char_to_str(char c);
int					digit_after_dollar(int j, char *str);
int					question_mark(char **tmp);
char				**ft_arrdup(char **arr);
size_t				equal_sign(char *str);

char				*check_dollar(t_tool *tool, char *str);
int					loop_dollar_sign(t_tool *tool, char *s, char **tmp, int j);
char				**expander(t_tool *tool, char **str);
char				*expander_str(t_tool *tool, char *str);
//t_simple_cmd		*call_expander(t_tool *tool, t_simple_cmd *cmd);

//minishell loop
char **build_av(t_tree *tree);
char	*cmd_finder(t_tree *tree, t_env *env);
void exec_rdr(t_tree *tree, t_env *env);
void exec_pipe(t_tree *tree, t_env *env);
void tree_exec(t_tree *tree, t_env *env);
void exec_cmd(t_tree *tree, t_env *env);


#endif
