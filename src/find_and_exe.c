/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:57 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/19 10:44:24 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	valid_cmds(char **cmds, int cmdnb)
{
	int	i;

	if (!cmds || !*cmds || !cmds[0])
		put_error("empty command");
	i = 0;
	while (i < cmdnb)
	{
		if (!cmds[i] || !cmds[i][0])
			put_error("empty command");
		i++;
	}
}

char	**find_paths(char **envp)
{
	char	**paths;

	if (!envp || !*envp)
		put_error("envp not found");
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp == NULL)
		put_error("PATH not found");
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		put_error("malloc");
	return (paths);
}

char	*exe_cmd(char **cmd, char **envp)
{
	char	**paths;
	char	*xpath;
	int		i;

	paths = find_paths(envp);
	i = 0;
	xpath = NULL;
	while (paths[i])
	{
		xpath = mod_strjoin(paths[i++], cmd[0]);
		if (!xpath)
			return (free_single(&xpath), free_str(paths), NULL);
		if (access(xpath, F_OK | X_OK) == 0)
		{
			if (execve(xpath, cmd, envp) == -1)
				return (free_single(&xpath), free_str(paths), "fail");
		}
		free_single(&xpath);
	}
	free_str(paths);
	free_single(&xpath);
	return (cmd[0]);
}
