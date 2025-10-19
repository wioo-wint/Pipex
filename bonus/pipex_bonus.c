/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:14:40 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/19 10:55:48 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_userinput(t_data *data, char **argv)
{
	char	*line;

	data->in_fd = open("here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->in_fd < 0)
		put_error(argv[1]);
	while (1)
	{
		write(1, "pipex 42> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free_single(&line);
			break ;
		}
		write(data->in_fd, line, ft_strlen(line));
		free_single(&line);
	}
	close(data->in_fd);
}

int	ft_here_doc(t_data *data, char **envp, char **argv, int ofile)
{
	int	status;

	get_userinput(data, argv);
	data->env = envp;
	status = 0;
	data->in_fd = open("here_doc_tmp", O_RDONLY);
	if (data->in_fd < 0)
		open_null(data, "here_doc_tmp", 'i');
	if (access(argv[ofile], F_OK) == 0 && access(argv[ofile], W_OK) == -1)
	{
		status = 1;
		open_null(data, argv[ofile], 'o');
	}
	else
	{
		data->out_fd = open(argv[ofile], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->out_fd < 0)
			perror(argv[ofile]);
	}
	return (status);
}
