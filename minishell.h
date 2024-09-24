/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:11:47 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/21 11:10:30 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//************************ header ************************//

# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h> 
# include <dirent.h>
# include <fcntl.h>

//**************** struct de spliter les arguments  **********************//

typedef struct s_split
{
	int		i;
	int		j;
	int		n;
	char	*buff;
	char	**result;
	int		s_quote;
	int		d_quote;
}		t_split;

//************** struct de commandes et rederictions  *********************//

typedef struct s_cmd
{
	char			**cmd;
	char			**red;
	int				*expd;
	int				fd_herdoc;
	int				ambiguous_redirect;
	int				cmd_count;
	int				red_count;
	struct s_cmd	*next;
}		t_cmd;

//**************** struct de  my environment variable  ************//

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

//*************** struct de  my environment variable   ********************//

typedef struct s_shell
{
	t_env	*my_env;
	t_cmd	*head;
	char	*input;
	char	**args;
	char	*stored_cwd;
	int		status;
}		t_shell;

//********************** struct de  exuc les arguments******************//

typedef struct s_info
{
	t_cmd	*cmd;
	t_shell	*shell;
	pid_t	*pids;
	int		n;
	int		saved_stdin;
	int		saved_stdout;
	int		(*pipefd)[2];
}		t_info;

int	g_heredoc_flag;

int		is_in_child(int x);
char	*read_in_line(void);
int		ft_parsing(char *line);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *str, int fd);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strlen(char *str);
char	*ft_strdup(char *src);
int		is_espace(char c);
char	*add_espace(char *line);
int		check_pipes(char *str);
char	**ft_split(char *str);
void	ft_free(char **str);
t_cmd	*fill_nodes(char **args);
int		ft_get_env(char **env, t_env **envt);
void	display_env(t_env *my_env);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t cursize, size_t newsize);
char	*ft_strndup(char *src, int n);
int		ft_isalnum(int c);
char	*ft_strchr(char *s, int c);
int		add_node_env(char *name, char *value, t_env **env);
void	update_env_value(t_env **env, char *key, char *value, int append);
int		is_identifier(char *str);
char	*remove_q(char *str);
int		check_red_out(char *line, int *i);
int		check_red_in(char *line, int *i);
int		check_q_p(char *line);
void	update_q(char c, int *s_quote, int *d_quote);
void	free_cmd(t_cmd *head);
void	free_env_list(t_env *env);
int		is_reds(char *c);
int		ft_isalpha(int c);
t_cmd	*new_cmd(int num_cmds, int num_reds);
int		check_key(t_env *env, char *key);
int		quotes(const char *str);
void	print_cmd_list(t_cmd *head);
char	*trim_espace(char *str);
int		exit_stat(int stat);
void	b_pwd(t_shell *shell);
size_t	count_q(char *str);
void	ft_export(t_cmd *cmd, t_env **env);
void	ft_unset(t_cmd *head, t_env **env);
void	exec_pwd(t_shell *shell, t_cmd *all_cmd);
void	ft_echo(t_cmd *cmd, t_env **env);
int		init_env(char **env, t_env **new_env);
int		ft_cd(t_cmd *cmd_list, t_env **env);
char	*ft_strjoin(char *s1, char *s2);
char	**splite(char const *str, char c);
char	**ft_freee(char **str);
void	display_env2(t_env *list);
char	**env_to_tab(t_env *env);
char	*get_path(char *cmd, char **env);
char	**env_to_tab(t_env *env);
void	execution(t_shell *shell);
void	expanding(t_shell *shell);
void	signal_handler(int signum);
char	*get_env_value_by_key(t_env *env, char *key);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *d, char *s, size_t l);
int		ft_count_w(char const *str, char c);
char	*ft_itoa(int n);
void	ft_exit(t_cmd *cmd);
char	*ft_strcat(char *d, char *s);
char	*ft_strstr(char *src, char *rech);
char	*ft_strcpy(char *d, char *s1);
int		cmd_size(t_cmd *head);
int		is_all_spaces(char *str);
char	*search_and_replace_env_var(char *cmd, t_env *env);
int		is_single_quotes(char *str, char *pos);
void	process_cmd(t_cmd *cmd);
int		ft_heredoc(t_shell *shell);
void	execute_command(t_cmd *cmd, t_env *env);
char	*get_env_value(char *env_line);
char	*get_env_key(char *env_line);
void	remove_q_all_cmd(t_cmd *cmd);
void	*ft_memmove(void *d1, const void *s1, size_t len);
char	*add_quotes(char *str);
char	*generate_unique_filename(void);
void	write_fd(int fd, char *str);
void	handle_signal_herdoc(int signum);
int		s_del(char *delimiter);
int		d_del(char *delimiter);
int		check_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, t_shell *shell);
void	set_st_ext(int exit_st, int N_exit);
int		is_directory(const char *path);
void	free_fil_args(char **filtered_cmd);
void	empty_args(t_info *info);
int		compare_pos1(char *str);
char	*ft_wildcard(char *pattern);
void	expand_wildcard(t_cmd *cmd, int *index);
int		count_w_test(char *str);
void	put_identifier(char *key, char *value);
void	child_process(t_info *info, int i);
void	reset_redirections(int saved_stdin, int saved_stdout);
long	int	mod(long int nbr);
void	builtin(t_info *info);
void	close_pipes(int pipefds[][2], int n);
void	create_pipes(int pipefds[][2], int n);
int		ft_isdigit(int c);
size_t	compte_arg(char **args);
void	exec_command_not_found(char *command);
int		red(char c);
int		get_strlen(char *str);
int		count_elements(char **str);
char	*copie_avant_d(char *result, int *res_len, char *cmd, int premier_len);
char	*get_env_1(char *name, t_env *my_env);
char	*get_value(char *cmd, char *value, char *result, int *res_len);
char	*append_result(char *result, int *res_len, char *value);
char	*get_var_value(char **cmd, t_env *env);
char	*rest_cmd(char *result, int res_len, char *cmd);
char	*get_var_value(char **cmd, t_env *env);
void	*ft_calloc(size_t count, size_t size);
void	handle_error(char *f_key, char *f_value);
void	ft_env(t_env *list);
void	exit_st(int nbr);
int		check_quotes1(char *str);
int		is_last_command_exit(t_cmd *cmd_list);
int		redirections(t_cmd *cmd);
char	*rest_cmd(char *result, int res_len, char *cmd);
void	expand_wildcard(t_cmd *cmd, int *index);
int		is_wildcard_quoted(char *str);
void	expand_cmd(t_cmd *cmd, t_env *env);
void	proc_env_var(char **str, t_env *env, int *expand);
char	**get_wildcard_results(char *wildcard, int *t_count);
void	insert_resul(t_cmd *cmd, char **wildcard_res, int *index, int t_count);
char	*ft_strjoin1(char *s1, char *s2);
int		update_or_add(t_env **env, char *key, char *value, int append);
void	update_cd_value(t_env **env, char *key, char *value, int append);
int		is_wildcard_quoted(char *str);
void	wait_pro(t_info *info);
int		update_cd_add(t_env **env, char *key, char *value, int append);
#endif