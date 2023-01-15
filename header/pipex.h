/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:04:03 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/15 23:14:02 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct st
{
	int		pipe[2];
	int		infile;
	int		outfile;
	int		id1;
	int		id2;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		status1;
	int		status2;
	int		status_code1;
	int		status_code2;
}			t_pipex;

void		err_msg(char *msg);
void		free_double_arr(char **arr);
void		free_ch(t_pipex *pipex);
void		free_p(t_pipex *pipex);
void		err(char *msg, char *p2, int errn);
char		**find_paths(char **envp);
void		close_pipe(int fd[]);
void		close_files(int infile, int outfile);
void		parrent(t_pipex pipex, char **av, char **envp);
void		second_child(t_pipex pipex, char **av, char **envp);
#endif
