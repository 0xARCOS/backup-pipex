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

int main(int argc, char **argv, char **envp)
{
    int infile;
    int outfile;

    if (argc != 5)
    {
        ft_putstr("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
        return 1;
    }

    // Validar existencia de infile
    infile = open(argv[1], O_RDONLY);
    if (infile < 0)
    {
        error_open(argv[1]);
        return 1;
    }
    //close(infile); tamos probanddo

    // Validar permisos de outfile (crea/trunca)
    outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfile < 0)
    {
        error_open(argv[4]);
        return 1;
    }
    //close(outfile); tamos probando

    // Ejecutar lógica principal
    //pipex(argv, envp);
    pipex(argv, envp, infile, outfile);

    return 0;
}

