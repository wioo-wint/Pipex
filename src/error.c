/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:28:37 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/17 17:35:44 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	put_error(char *reason)
{
	write(2, "pipex:", 6);
	perror(reason);
	if (!ft_strncmp(reason, "execve_command", 14))
		exit(127);
	exit(EXIT_FAILURE);
}
