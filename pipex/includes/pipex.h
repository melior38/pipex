/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:14:09 by asouchet          #+#    #+#             */
/*   Updated: 2023/03/31 18:26:35 by asouchet         ###   ########.fr       */
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

typedef struct s_setup {
	char	**av;
	char	**env;
}				t_setup;

void	ft_get_path(t_data *path, char *av, char **env);
int		improved_dup2(int fildes, int fildes2);
int		improved_pipe(int *fd);
pid_t	improved_fork(void);
void	free_tab(char **split);
int		first_fork(int *file, int *fd, t_setup *setup, t_data *data);
int		last_fork(int *file, int *fd, t_setup *setup, t_data *data);
void	fd_copy(int *dst, int *src);
void	close_and_wait(int *fd, int *pid, int i);
void	pipex(int ac, t_setup *setup, int *fd, t_data *data);

#endif