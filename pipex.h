/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ari <ari@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:01:15 by aarcos            #+#    #+#             */
/*   Updated: 2025/05/15 04:36:46 by ari              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// void pipex(char **argv, char **envp);
void	pipex(char **argv, char **envp, int infile, int outfile);

void	execute(char *cmd, char **envp);
char	*ft_strndup(const char *s, int len);
char	*ft_strdup(const char *s1);

char	*get_command_path(char *cmd, char **envp);
void	ft_putstr_fd(const char *s, int fd);
void	ft_free_split(char **arr);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
void	ft_putstr(char *s, int fd);
int		ft_strlen(char const *s);
char	*ft_strjoin(char const *s1, char *s2);

void	error_open(const char *path);
void	error_cmd(const char *cmd);

// split
char	**ft_split_args(const char *s, char delim);
int		is_delim(char c, char delim);
// char	*extract_arg(const char **s, char delim);

#endif
