/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:25 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/15 23:21:48 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	err_msg(char *msg)
{
	perror(msg);
	exit(1);
}

void	err(char *msg, char *p2, int errn)
{
	write(2, msg, ft_strlen(msg));
	write(2, p2, ft_strlen(p2));
	write(2, "\n", 1);
	exit(errn);
}

void	parrent(t_pipex pipex, char **av, char **envp)
{
	pipex.id2 = fork();
	if (pipex.id2 == 0)
		second_child(pipex, av, envp);
	(close_pipe(pipex.pipe), close_files(pipex.infile, pipex.outfile));
	waitpid(pipex.id1, &pipex.status1, 0);
	if (WIFEXITED(pipex.status1))
		pipex.status_code1 = WEXITSTATUS(pipex.status1);
	waitpid(pipex.id2, &pipex.status2, 0);
	if (WIFEXITED(pipex.status2))
	{
		pipex.status_code2 = WEXITSTATUS(pipex.status2);
		if (pipex.status_code2)
			exit(pipex.status_code2);
	}
}
