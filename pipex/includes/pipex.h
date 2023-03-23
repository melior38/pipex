/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:14:09 by asouchet          #+#    #+#             */
/*   Updated: 2023/03/23 14:23:27 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data {
	char	**splited_path;
	char	*path;
	char	**flag;
	int		i;
}				t_data;

void	ft_get_path(t_data *path, char *av, char **env);
int		improved_dup2(int fildes, int fildes2);
int		improved_pipe(int *fd);
pid_t	improved_fork(void);
void	free_tab(char **split);
int		first_fork(int *file, int *fd, char **av, t_data *data, char **env);
int		last_fork(int *file, int *fd, char **av, t_data *data, char **env);

#endif