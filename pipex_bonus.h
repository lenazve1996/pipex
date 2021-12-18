/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:31:28 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/18 16:50:38 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

char	*ft_free_str(char *str);
char	***ft_free_mem(char **path, int **pipes, int proc_num, char ***cmd_arr);
void	ft_parsing(int argc, char **argv, int *process_num, int *cmd_index);
char	***ft_parse_cmd(int process_num, int cmd_index, char **argv, int argc);
char	**ft_memory_alloc_path(int process_num);
int		**ft_create_pipes(int process_num);
void	ft_close_unused_pipes_child(int i, int **pipes, int process_num);
void	ft_close_unused_pipes_parent(int **pipes, int process_num);
void	ft_make_child(int proc_num, int **pipes, char **path, char ***cmd_arr);
void	ft_read_in_loop(int in_fd, int out_fd, char *stop_val);
void	ft_read_input(char *infile, int first_pipe, int cmd_index, char **argv);
void	ft_write_output(char *outfile, int last_pipe, int cmd_index);
void	ft_waiting_childs(int process_num);
void	ft_error_processing(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_parsing_path(char ***array, char **path, int process_num);

#endif