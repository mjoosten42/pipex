/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:12:26 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/04 17:29:30 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "fcntl.h"
# include "unistd.h"

char	**ft_getpaths(char **env);
void	ft_getpath(char **strs, char **env);
void	ft_cmd(char	**argv, int fds[2], int close);

#endif