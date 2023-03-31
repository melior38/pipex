/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:04:11 by asouchet          #+#    #+#             */
/*   Updated: 2023/03/31 18:16:48 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_fork(int *file, int *fd, t_setup *setup, t_data *data)
{
	int	pid;

	improved_pipe(fd);
	pid = improved_fork();
	if (pid == 0)
	{
		close(fd[0]);
		close(file[1]);
		printf("first fork\n");
		improved_dup2(file[0], STDIN_FILENO);
		improved_dup2(fd[1], STDOUT_FILENO);
		data->flag = ft_split(setup->av[2], ' ');
		ft_get_path(data, setup->av[2], setup->env);
		execve(data->splited_path[data->i], data->flag, setup->env);
		exit(1);
	}
	close(file[0]);
	return (pid);
}

int	last_fork(int *file, int *fd, t_setup *setup, t_data *data)
{
	int	pid;

	pid = improved_fork();
	if (pid == 0)
	{
		close(fd[1]);
		printf("last fork\n");
		improved_dup2(file[1], STDOUT_FILENO);
		improved_dup2(fd[0], STDIN_FILENO);
		data->flag = ft_split(setup->av[3], ' ');
		ft_get_path(data, setup->av[3], setup->env);
		execve(data->splited_path[data->i], data->flag, setup->env);
		exit(1);
	}
	close(file[1]);
	return (pid);
}

int	middle_fork(int *tmp, int *fd, t_setup *setup, t_data *data)
{
	int	pid;

	pid = improved_fork();
	if (pid == 0)
	{
		close(fd[0]);
		close(tmp[1]);
		printf("middle fork\n");
		improved_dup2(fd[1], STDOUT_FILENO);
		improved_dup2(tmp[0], STDIN_FILENO);
		close(tmp[1]);
		close(fd[0]);
		data->flag = ft_split(setup->av[3], ' ');
		ft_get_path(data, setup->av[3], setup->env);
		execve(data->splited_path[data->i], data->flag, setup->env);
		exit(1);
	}
	close(tmp[0]);
	close(tmp[1]);
	return (pid);
}

void	close_and_wait(int *fd, int *pid, int i)
{
	close(fd[0]);
	close(fd[1]);
	while (i >= 0)
		wait(&pid[i--]);
	free(pid);
}

void	pipex(int ac, t_setup *setup, int *files, t_data *data)
{
	int	fd[2];
	int	*pid;
	int	i;
	int	tmp[2];

	pid = malloc(sizeof(int *) * ac - 3);
	if (!pid)
		exit(1);
	pid[0] = first_fork(files, fd, setup, data);
	i = 3;
	if (ac > 5)
	{
		while (i < ac - 2)
		{
			fd_copy(tmp, fd);
			improved_pipe(fd);
			pid[i - 2] = middle_fork(tmp, fd, setup, data);
			i++;
		}
	}
	pid[i] = last_fork(files, fd, setup, data);
	close_and_wait(fd, pid, i);
}
