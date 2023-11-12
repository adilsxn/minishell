#ifndef MSH_ENV_H
#define MSH_ENV_H


typedef struct s_msh_env
{
    const char *key;
    const char *value;
    struct s_msh_env *next;
} t_msh_env;

typedef struct s_msh_envlist
{
    t_msh_env *head;
    int size;
} t_msh_envlist;


t_msh_envlist *mk_msh_envlist();
int add_msh_env(t_msh_envlist *list, const char *key, const char *value);
int del_msh_env(t_msh_envlist *list, const char *key);
char *lookup_msh_env(t_msh_envlist *list, const char *key);
int traverse_msh_env(t_msh_envlist *list);
int del_msh_envlist(t_msh_envlist *list);
#endif 
