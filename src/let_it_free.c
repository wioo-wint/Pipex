/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_it_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:52:50 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/17 15:45:57 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_str(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	free_single(char **str)
{
	if (str && *str)
	{
		free (*str);
		*str = NULL;
	}
}

void	close_all(t_data *data)
{
	if (data->pipefd[0] >= 0)
		close(data->pipefd[0]);
	if (data->pipefd[1] >= 0)
		close(data->pipefd[1]);
	if (data->in_fd >= 0)
		close(data->in_fd);
	if (data->out_fd >= 0)
		close(data->out_fd);
}
