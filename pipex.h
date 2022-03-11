/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:12:26 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/11 11:49:02 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "fcntl.h"
# include "unistd.h"

char	**ft_getpaths(char **env);
char	*ft_getpath(char **strs, char **env);
pid_t	ft_cmd(char	**argv, int fds[2]);

#endif