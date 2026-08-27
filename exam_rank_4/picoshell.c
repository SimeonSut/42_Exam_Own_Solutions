/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:16:17 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/28 00:16:20 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>

static void	command_execution(char **cmds[], int read_fd, int *pipe_fd, int i);
static int	waiting_loop(void);

int		picoshell(char **cmds[])
{
	int		pipe_fd[2];
	int		read_fd;
	int		i;
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (1);
	read_fd = pipe_fd[0];
	i = 0;
	while (cmds[i])
	{
		if (i > 0 && pipe(pipe_fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			command_execution(cmds, read_fd, pipe_fd, i);
		if (pid != 0)
		{
			if (i > 0)
				close(read_fd);
			read_fd = pipe_fd[0];
			close(pipe_fd[1]);
		}
		i++;
	}
	waiting_loop();
	return (0);
}

static void	command_execution(char **cmds[], int read_fd, int *pipe_fd, int i)
{
	if (i > 0)
	{
		if (dup2(read_fd, STDIN_FILENO) == -1)
		{
			close(read_fd);
			close(pipe_fd[1]);
			exit(1);
		}
	}
	if (cmds[i + 1])
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close(read_fd);
			close(pipe_fd[1]);
			exit(1);
		}
	}
	close(read_fd);
	close(pipe_fd[1]);
	execvp(cmds[i][0], cmds[i]);
	exit(1);
}

static void		waiting_loop(void)
{
	int	wstatus;

	while (wait(&wstatus) > 0)
	{
		if (WIFEXITED(wstatus) == true && WEXITSTATUS(wstatus) != 0)
			exit(1);
	}
	exit(0);
}
