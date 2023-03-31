/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:13:53 by asouchet          #+#    #+#             */
/*   Updated: 2023/03/31 05:12:57 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* les differents type de fd sont les suivant:
	- stdin = fd[0] used to redirect
	- stdout = fd[1] -> flush into your screen whit a buffer / write / 
	- stderror = fd[2]  write /
*/
		// error = access(data->splited_path[j], X_OK);
		// if (error == 0)	
		// 	break ;
		// else if(error == -1)
		// {
		// 	perror("error");
		// 	exit(1);
		// }
		
void	ft_get_path(t_data *data, char *av, char **env)
{
	int		j;
	
	j = 0;
	while (ft_strncmp(env[j], "PATH=", 5))
		j++;
	data->path = ft_strtrim(env[j], "PATH=");
	data->splited_path = ft_split(data->path, ':');
	free(data->path);
	data->flag = ft_split(av, ' ');
	j = 0;
	while (data->splited_path[j])
	{
		data->splited_path[j] = ft_strjoin(data->splited_path[j], "/");
		data->splited_path[j] = ft_strjoin(data->splited_path[j], data->flag[0]);
		if (access(data->splited_path[j], X_OK) == 0)
			break ;
		free(data->splited_path[j]);
		j++;
	}
	data->i = j;
}


int main(int ac, char **av, char **env)
{
	// access (access(const char *path, int mode);)
	// path (tu le recupere en parcourant le tableau env) 1er etape
	// execve
	// improved_dup2 (improved_dup2(int stdin, int stdout);) / la stdouot est rediriger dans stdin
	// process (child) fork watch
	t_data	data;
	t_setup	setup;
	int		file[2];
	
	setup.env = env;
	setup.av = av;
	if (ac <= 4)
	{
		ft_putstr_fd("error not enough arguement\n", 2);
		ft_putstr_fd("pipex will close\n", 2);
		exit(1);
	}
	file[0] = open(av[1], O_RDONLY); // check error
	file[1]	= open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644); // same
	if (file[0] < 0 || file[1] < 0)
	{
		ft_putstr_fd("error: infile or outfile non existant\n", 2);
		ft_putstr_fd("pipex will close\n", 2);
		exit(1);
	}
	pipex(ac, &setup, file, &data);
	exit(0);
}