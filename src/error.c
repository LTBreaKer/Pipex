/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:25 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/11 03:16:48 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	err_msg(char *msg)
{
	perror(msg);
	exit(1);
}

void	err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	check_cmd1(t_pipex pipex, char *av, char **paths)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(av, ' ');
	while (paths[i])
	{
		pipex.cmd = ft_strjoin2(paths[i], "/");
		pipex.cmd = ft_strjoin(pipex.cmd, tmp[0]);
		if (access(pipex.cmd, F_OK) == 0)
			break ;
		free(pipex.cmd);
		i++;
	}
	free_double_arr(tmp);
	free_double_arr(paths);
	if (access(pipex.cmd, F_OK) == 0)
	{
		free(pipex.cmd);
		return ;
	}
	perror("Error");
	exit(-1);
}

void	check_cmd2(t_pipex pipex, char *av, char **paths)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(av, ' ');
	while (paths[i])
	{
		pipex.cmd = ft_strjoin2(paths[i], "/");
		pipex.cmd = ft_strjoin(pipex.cmd, tmp[0]);
		if (access(pipex.cmd, F_OK) == 0)
			break ;
		free(pipex.cmd);
		i++;
	}
	free_double_arr(tmp);
	free_double_arr(paths);
	if (access(pipex.cmd, F_OK) == 0)
	{
		free(pipex.cmd);
		return ;
	}
	perror("Error");
	exit(-1);
}

void	check_cmd(t_pipex pipex, char **av, char **envp)
{
	check_cmd1(pipex, av[2], find_paths(envp));
	check_cmd2(pipex, av[3], find_paths(envp));
}
