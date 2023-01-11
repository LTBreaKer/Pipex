/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:08:39 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/11 03:23:21 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	*get_cmd(char *cmd, t_pipex pipex)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(cmd, ' ');
	while (pipex.cmd_paths[i])
	{
		pipex.cmd = ft_strjoin(pipex.cmd_paths[i], "/");
		pipex.cmd = ft_strjoin(pipex.cmd, tmp[0]);
		if (access(pipex.cmd, F_OK) == 0)
			break ;
		free(pipex.cmd);
		i++;
	}
	free_double_arr(tmp);
	return (pipex.cmd);
}

void	first_child(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.pipe[1], STDOUT_FILENO);
	close(pipex.pipe[0]);
	dup2(pipex.infile, STDIN_FILENO);
	close(pipex.pipe[1]);
	close(pipex.infile);
	pipex.cmd = get_cmd(av[2], pipex);
	pipex.cmd_args = ft_split(av[2], ' ');
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	close(pipex.pipe[0]);
	close(pipex.outfile);
	pipex.cmd = get_cmd(av[3], pipex);
	pipex.cmd_args = ft_split(av[3], ' ');
	execve(pipex.cmd, pipex.cmd_args, envp);
}

char	**find_paths(char **envp)
{
	char	**paths;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!ft_strncmp("PATH", *envp, 4))
	{
		paths = ft_split(*envp + 5, ':');
		return (paths);
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		err("Error: invalid arguments\n");
	if (pipe(pipex.pipe) == -1)
		err("Error: can't create pipe\n");
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile == -1)
		err_msg("Error");
	pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (pipex.outfile == -1)
		err_msg("Error");
	pipex.cmd_paths = find_paths(envp);
	check_cmd(pipex, av, envp);
	pipex.id1 = fork();
	if (pipex.id1 == 0)
		first_child(pipex, av, envp);
	pipex.id2 = fork();
	if (pipex.id2 == 0)
		second_child(pipex, av, envp);
	close_pipe(pipex.pipe);
	close_files(pipex.infile, pipex.outfile);
	waitpid(pipex.id1, NULL, 0);
	waitpid(pipex.id2, NULL, 0);
}
