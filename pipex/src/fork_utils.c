/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:04:11 by asouchet          #+#    #+#             */
/*   Updated: 2023/03/23 14:23:21 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int first_fork(int *file, int *fd, char **av, t_data *data, char **env)
{
	int pid;

	pid = improved_fork();
	if (pid == 0) // tu veut recup infile dans cmd1 et dans le else mettre dans la cmd2
	{
		close(fd[0]);
		close(file[1]);
		improved_dup2(file[0], STDIN_FILENO);
		improved_dup2(fd[1], STDOUT_FILENO);
		data->flag = ft_split(av[2], ' ');
		ft_get_path(data, av[2], env);
		execve(data->splited_path[data->i], data->flag, env);
		exit(1);
	}
	return (pid);
}

int last_fork(int *file, int *fd, char **av, t_data *data, char **env)
{
	int pid;

	pid = improved_fork();
	if(pid == 0)
	{
		close(fd[1]);
		close(file[0]);
		improved_dup2(file[1], STDOUT_FILENO);
		improved_dup2(fd[0], STDIN_FILENO);
		data->flag = ft_split(av[3], ' '); // free tab
		ft_get_path(&data, av[3], env);
		execve(data->splited_path[data->i], data->flag, env);
		exit(1);
	}
}

// int middle_fork(int *file, int *fd, char **av, t_data *data, char **env)
// {
// 	int pid;

// 	pid = improved_fork();
// 	if(pid == 0)
// 	{
// 		close(fd[1]);
// 		close(file[0]);
// 		improved_dup2(file[1], STDOUT_FILENO);
// 		improved_dup2(fd[0], STDIN_FILENO);
// 		data->flag = ft_split(av[3], ' '); // free tab
// 		ft_get_path(&data, av[3], env);
// 		execve(data->splited_path[data->i], data->flag, env);
// 		exit(1);
// 	}
// }