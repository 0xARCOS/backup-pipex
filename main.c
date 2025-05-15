/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 12:00:47 by aarcos            #+#    #+#             */
/*   Updated: 2025-04-11 12:00:47 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	open_infile(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_open(path);
	return (fd);
}

static int	open_outfile(char *path)
{
	int fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_open(path);
	return (fd);
}

int	main(int argc, char **argv, char **envp)
{
	int infile;
	int outfile;

	if (argc != 5)
	{
		ft_putstr("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	infile = open_infile(argv[1]);
	outfile = open_outfile(argv[4]);
	pipex(argv, envp, infile, outfile);
	return (0);
}