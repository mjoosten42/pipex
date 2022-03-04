/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:13:06 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/04 17:38:29 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	**strs;
	int		fds[2];
	int		pipes[2];

	if (argc < 5)
		return (1);
	pipe(pipes);
	strs = ft_split(argv[2], ' ');
	ft_getpath(strs, env);
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = pipes[1];
	ft_cmd(strs, fds, 1);
	ft_free_array(strs);
	strs = ft_split(argv[3], ' ');
	ft_getpath(strs, env);
	fds[0] = pipes[0];
	fds[1] = open(argv[4], O_CREAT | O_WRONLY, 0666);
	ft_cmd(strs, fds, 1);
	ft_free_array(strs);
	exit(EXIT_SUCCESS);
}

void	ft_cmd(char	**argv, int fds[2], int fd_close)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		execve(*argv, argv, 0);
		ft_error(0);
	}
	close(fds[fd_close]);
	waitpid(pid, 0, 0);
}

void	ft_getpath(char **strs, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	paths = ft_getpaths(env);
	path = ft_strjoin(paths[i++], *strs);
	while (access(path, F_OK))
	{
		free(path);
		if (!paths[i])
			break ;
		path = ft_strjoin(paths[i++], *strs);
	}
	free(*strs);
	*strs = path;
	ft_free_array(paths);
}

char	**ft_getpaths(char **env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 4))
		i++;
	paths = ft_split(env[i], ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = path;
		i++;
	}
	return (paths);
}
