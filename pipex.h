/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:51:08 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/19 10:57:33 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct p_data
{
	int		in_fd;
	int		out_fd;
	char	**env;
	int		pipefd[2];
	pid_t	pid;
}	t_data;

// Libft
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*mod_strjoin(const char *s1, const char *s2);

// Pipex
void	put_error(char *reason);
void	free_str(char **s);
void	free_single(char **str);
void	close_all(t_data *data);

void	open_null(t_data *data, char *reason, char io);
int		init_data(t_data *data, char **envp, char **argv, int ofile);
void	valid_cmds(char **cmds, int cmdnb);
void	redirect_stdio(int infd, int outfd);
char	*exe_cmd(char **cmd, char **envp);
void	exe_childprocess(t_data *data, char *cmds);
int		ft_pipex(t_data *data, int cmdnb, char **cmds);

int		ft_here_doc(t_data *data, char **envp, char **argv, int ofile);

#endif