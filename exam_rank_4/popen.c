/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:16:08 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/28 00:16:10 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!file || !argv || !argv[0] || (type != 'r' && type != 'w'))
		return (1);
	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				exit(1);
			}
		}
		else
		{
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				exit(1);
			}
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execvp(file, argv);
		return (1);
	}
	if (type == 'r')
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	else if (type == 'w')
	{
		close(pipe_fd[0]);
		return (pipe_fd[1]);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}
