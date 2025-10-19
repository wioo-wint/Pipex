/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 11:03:57 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/19 10:57:22 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_null(t_data *data, char *reason, char io)
{
	int	fd;

	perror(reason);
	fd = open("/dev/null", O_RDONLY);
	if (fd < 0)
		put_error("/dev/null");
	if (io == 'i')
		data->in_fd = fd;
	else
		data->out_fd = fd;
}

int	init_data(t_data *data, char **envp, char **argv, int ofile)
{
	int	status;

	data->env = envp;
	status = 0;
	data->in_fd = open(argv[1], O_RDONLY);
	if (data->in_fd < 0)
		open_null(data, argv[1], 'i');
	if (access(argv[ofile], F_OK) == 0 && access(argv[ofile], W_OK) == -1)
	{
		status = 1;
		open_null(data, argv[ofile], 'o');
	}
	else
	{
		data->out_fd = open(argv[ofile], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			perror(argv[ofile]);
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		fstatus;
	int		status;

	if (argc < 5)
		put_error("bad arguments, try ./pipex infile cmd1 cmd2 outfile");
	status = 0;
	if (ft_strncmp(argv[1], "here_doc", 8))
	{
		valid_cmds(&argv[2], argc - 3);
		fstatus = init_data(&data, envp, argv, argc - 1);
		status = ft_pipex(&data, argc - 3, &argv[2]);
	}
	else
	{
		valid_cmds(&argv[3], argc - 4);
		fstatus = ft_here_doc(&data, envp, argv, argc - 1);
		status = ft_pipex(&data, argc - 4, &argv[3]);
		unlink("here_doc_tmp");
	}
	if (fstatus == 1)
		status = 1;
	close_all(&data);
	return (status);
}
