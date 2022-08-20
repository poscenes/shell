/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:28:21 by tjamis            #+#    #+#             */
/*   Updated: 2022/08/20 17:17:59 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>

typedef struct s_info
{
	char	**envp;
	char	**history;
	int		status;
	int		pid;
}t_info;

typedef struct s_cmd_data
{
	int		fd_in_out[3];
	int		fd_close[2];
	char	**cmd_arg;
}	t_cmd_data;

t_info	g_info;

typedef struct s_parser_data
{
	t_cmd_data	*cmds;
	char		**line_split;
	char		**curr_cmd;
	char		*curr_word;
	int			size;
}	t_parser_data;

# define READ_FD 0
# define WRITE_FD 1
# define ERR_FD 2

/*PARSER*/
void		parser(char *line);
char		*quotation(char *line, int *i, int *flag);
int			redirect(t_cmd_data *cmds, char *redirect, char *filename);
void		line_shift(char *line, int i, int shift);
int			ft_isredirect(char ch1, char ch2);
char		**pre_parsing(char **line);
char		*delete_isspace(char *line);
int			is_key(char ch);
char		**error_message(char ***line_split, int i);
char		**error_quotes(char ***line_split);
int			free_if_error(t_cmd_data *comand);
int			ft_isspace(char ch);
int			special_symbol(char *line);
void		add_str(char *line, int *i, int *start, char ***line_split);
void		file_descriptors(t_cmd_data *cmds);
void		cmd_fd(t_cmd_data *cmds, int size);
void		wildcards(t_parser_data *data, int j);
void		parse_env(t_parser_data *data, int *j);
int			env_parsing(t_parser_data *data, int *j);
void		add_cmd(t_cmd_data *cmds, int size, char *str);
int			check_size(char **line);
/*env function*/
void		sigint_heredoc(int sign_num);
char		*get_env(char *str);
char		*env_list(char *line, int *i);
char		**copy_envp(char **envp);
/*function for double*/
void		free_array(char **arr);
int			arr_size(char **arr);
void		char_arr_sort(char **env);
void		rl_clear_history(void);
void		rl_replace_line(const char *text, int clear_undo);

#endif
