/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:08:39 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/17 22:51:24 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	*get_cmd(char *cmd, t_pipex pipex)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(cmd, ' ');
	if (access(tmp[0], F_OK) == 0)
		return (tmp[0]);
	if (!pipex.cmd_paths)
		return (NULL);
	while (pipex.cmd_paths[i])
	{
		pipex.cmd = ft_strjoin2(pipex.cmd_paths[i++], "/");
		pipex.cmd = ft_strjoin(pipex.cmd, tmp[0]);
		if (access(pipex.cmd, F_OK) == 0)
			break ;
		free(pipex.cmd);
	}
	free_double_arr(tmp);
	if (access(pipex.cmd, F_OK) == 0)
		return (pipex.cmd);
	return (NULL);
}

void	first_child(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.pipe[1], STDOUT_FILENO);
	close(pipex.pipe[0]);
	if (pipex.infile == -1)
		exit(1);
	dup2(pipex.infile, STDIN_FILENO);
	close(pipex.pipe[1]);
	close(pipex.infile);
	close(pipex.outfile);
	pipex.cmd = get_cmd(av[2], pipex);
	if (!pipex.cmd)
		err("command not found: ", av[2], 127);
	pipex.cmd_args = ft_split(av[2], ' ');
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		perror("");
	exit(126);
}

void	second_child(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.pipe[0], STDIN_FILENO);
	close(pipex.pipe[1]);
	if (pipex.outfile == -1)
		exit(1);
	dup2(pipex.outfile, STDOUT_FILENO);
	close(pipex.pipe[0]);
	close(pipex.outfile);
	close(pipex.infile);
	pipex.cmd = get_cmd(av[3], pipex);
	if (!pipex.cmd)
		err("command not found: ", av[3], 127);
	pipex.cmd_args = ft_split(av[3], ' ');
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		perror(pipex.cmd);
	exit(126);
}

char	**find_paths(char **envp)
{
	char	**paths;

	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (*envp && !ft_strncmp("PATH", *envp, 4))
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
		err("Error: invalid arguments", "", 1);
	if (pipe(pipex.pipe) == -1)
		err("Error: can't create pipe", "", 1);
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile == -1)
		perror(av[1]);
	pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipex.outfile == -1)
		perror(av[ac - 1]);
	pipex.cmd_paths = find_paths(envp);
	pipex.id1 = fork();
	if (pipex.id1 == 0)
		first_child(pipex, av, envp);
	else
		parrent(pipex, av, envp);
}
