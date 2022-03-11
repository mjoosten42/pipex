/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:13:06 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/11 12:03:04 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	char	**strs;
	int		pipes[2];
	int		fds[2];
	int		ret;

	if (argc < 5)
		return (1);
	pipe(pipes);
	strs = ft_split(argv[2], ' ');
	*strs = ft_getpath(strs, env);
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = pipes[1];
	ft_cmd(strs, fds);
	ft_free_array(strs);
	strs = ft_split(argv[3], ' ');
	*strs = ft_getpath(strs, env);
	fds[0] = pipes[0];
	fds[1] = open(argv[4], O_CREAT | O_WRONLY, 0644);
	pid = ft_cmd(strs, fds);
	ft_free_array(strs);
	waitpid(pid, &ret, 0);
	return (WEXITSTATUS(ret));
}

pid_t	ft_cmd(char	**argv, int fds[2])
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
	close(fds[0]);
	close(fds[1]);
	return (pid);
}

char	*ft_getpath(char **strs, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	paths = ft_getpaths(env);
	path = ft_strjoin(paths[i++], *strs);
	while (access(path, F_OK | X_OK))
	{
		free(path);
		if (!paths[i])
			ft_error("Command not found\n");
		path = ft_strjoin(paths[i++], *strs);
	}
	ft_free_array(paths);
	free(*strs);
	return (path);
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
