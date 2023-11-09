/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:14:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/09 18:12:14 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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

//parser
typedef struct s_parser_tool
{
	t_lexer			*lexer;
	t_lexer			*redirect;
	int				nb_redirect;
	struct s_tool	*tool;
}t_parser_tool;

typedef struct s_tool
{
	char					*arg;
	t_lexer					*lexer;
	struct s_simple_cmd		*simple_cmd;
	char					**env;
	char					*pwd;
	char					*old_pwd;
	char					**path;
	int						pipes;
	bool					reset;
}t_tool;

typedef struct s_simple_cmd
{
	char					**str;
	int						nb_redirect;
	t_lexer					*redirect;
	struct s_simple_cmd		*next;
	struct s_simple_cmd		*prev;
}t_simple_cmd;

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
int					parser(t_tool *tool);
t_simple_cmd		*init_cmd(t_parser_tool *parser_tool);
t_parser_tool		init_parser_tool(t_lexer *lexer_list, t_tool *tool);
void				init_tool(t_tool *tool);
void				free_array(char **array);
void				reset_tool(t_tool *tool);

void				count_pipes(t_lexer *lexer_list, t_tool *tool);
int					count_arg(t_lexer *lexer_list);
int					pipe_error(t_tool *tool);
int					ft_error(int error, t_tool *tool, t_lexer *lexer_list);
int					double_token_error(t_tool *tool);

t_simple_cmd		*cmd_new(char **str, int nb_redirect, t_lexer *redirect);
void				add_cmd(t_simple_cmd **lst, t_simple_cmd *new);
void				cmd_clear(t_simple_cmd **lst);
void				rm_redirect(t_parser_tool *parser_tool);
int					add_new_redirect(t_lexer *tmp, t_parser_tool *parser_tool);

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

//env
int					find_pwd(t_tool *tool);
char				*find_path(char **env);
int					parse_env(t_tool *tool);
int					check_var(t_tool *tool, char *str);
int					check_param(char *str);
char				**loop_add_var(char **array, char **final, char *str);
char				**add_var(char **array, char *str);
int					exportation(t_tool *tool, t_simple_cmd *cmd);
int					export_error(char *c);
int					envi(t_tool *tool);
int					check_identifier(char c);

#endif
