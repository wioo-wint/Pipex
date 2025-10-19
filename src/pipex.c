/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 11:07:26 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/17 18:42:42 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// why redirect from stdio fds to file and pipe fds?
// stdin(keyboard) and stdout(terminal)
// but we want cmds read input as infile and write output as outfile
// no redirect mean not connected cmds and files. so no pipeline
void	redirect_stdio(int infd, int outfd)
{
	if (infd != STDIN_FILENO)
	{
		if (dup2(infd, STDIN_FILENO) == -1)
			put_error("dup2");
		close(infd);
	}
	if (outfd != STDOUT_FILENO)
	{
		if (dup2(outfd, STDOUT_FILENO) == -1)
			put_error("dup2");
		close(outfd);
	}
}

void	exe_childprocess(t_data *data, char *cmds)
{
	char	**cmd;

	cmd = ft_split(cmds, ' ');
	if (!cmd)
		return (free_str(cmd), put_error("command"));
	data->pid = fork();
	if (data->pid < 0)
		put_error("fork");
	if (data->pid == 0)
	{
		redirect_stdio(data->in_fd, data->pipefd[1]);
		if (data->pipefd[0] != -1 && data->pipefd[0] != data->in_fd)
			close(data->pipefd[0]);
		if (data->pipefd[1] != -1 && data->pipefd[1] != STDOUT_FILENO)
			close(data->pipefd[1]);
		if (ft_strncmp(exe_cmd(cmd, data->env), "success", 7))
			return (free_str(cmd), put_error("execve_command"));
	}
	free_str(cmd);
	if (data->pipefd[1] != data->out_fd)
		close(data->pipefd[1]);
	if (data->in_fd != -1 && data->in_fd != STDIN_FILENO)
		close(data->in_fd);
	data->in_fd = data->pipefd[0];
}

int	ft_pipex(t_data *data, int cmdnb, char **cmds)
{
	pid_t	pids[1024];
	int		i;
	int		status;

	i = 0;
	while (cmds[i] && i < cmdnb)
	{
		if (i < cmdnb - 1)
		{
			if (pipe(data->pipefd) == -1)
				put_error("pipe");
		}
		else
		{
			data->pipefd[0] = -1;
			data->pipefd[1] = data->out_fd;
		}
		exe_childprocess(data, cmds[i]);
		pids[i++] = data->pid;
	}
	i = 0;
	while (i < cmdnb)
		waitpid(pids[i++], &status, 0);
	return (status / 256);
}

// WIFEXITED - child exit normally
// WIFSIGNALED - child killed by signal like segfaults
// WTERMSIG - we add 128 to match std shell exit code
// int	waitfor_child(int cmdnb, pid_t *pids)
// {
// 	int	i;
// 	int	status;

// 	i = 0;
// 	while (i < cmdnb)
// 		waitpid(pids[i++], &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	if (WIFSIGNALED(status))
// 		return (128 + WTERMSIG(status));
// 	return (status / 256);
// }
