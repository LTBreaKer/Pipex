/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:04:03 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/10 03:45:41 by aharrass         ###   ########.fr       */
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
}			t_pipex;

void		err_msg(char *msg);
void		free_double_arr(char **arr);
void		free_ch(t_pipex *pipex);

#endif