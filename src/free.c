/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 23:46:42 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/11 03:29:40 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	free_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_ch(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
		free(pipex->cmd_paths[i++]);
	free(pipex->cmd_paths);
}

void	free_p(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
		free(pipex->cmd_paths[i++]);
	free(pipex->cmd_paths);
}

void	close_pipe(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

void	close_files(int infile, int outfile)
{
	close(infile);
	close(outfile);
}
