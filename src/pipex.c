/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:08:39 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/09 23:12:56 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	*get_cmd(char *cmd, t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.cmd_paths[i])
	{
		pipex.cmd = ft_strjoin(pipex.cmd_paths[i], "/");
		pipex.cmd = ft_strjoin(pipex.cmd, cmd);
		if (access(pipex.cmd, F_OK) == 0)
			break ;
		free(pipex.cmd);
		i++;
	}
	if (access(pipex.cmd, F_OK) == 0)
		return (pipex.cmd);
	return (NULL);
}

void	first_child(t_pipex pipex, char **av, char **envp)
{
	char *args[] = {"-l", NULL};
	dup2(pipex.pipe[1], STDOUT_FILENO);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	pipex.cmd = get_cmd(av[1], pipex);
	if (!pipex.cmd)
		err_msg("Error: Command not found\n");
	execve(pipex.cmd, args, envp);
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

	if (ac < 5)
		err_msg("Error: invalid arguments\n");
	if (pipe(pipex.pipe) == -1)
		err_msg("Error: can't create pipe\n");
	pipex.cmd_paths = find_paths(envp);
	pipex.id1 = fork();
	if (pipex.id1 == -1)
		err_msg("Error: pipe not created\n");
	if (pipex.id1 == 0)
		first_child(pipex, av, envp);
	waitpid(pipex.id1, NULL, 0);
}
