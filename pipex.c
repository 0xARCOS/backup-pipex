/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 12:01:04 by aarcos            #+#    #+#             */
/*   Updated: 2025-04-11 12:01:04 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute(char *cmd, char **envp)
{
    char    **args;
    char    *cmd_path;

    if (!cmd || !*cmd)
    {
        ft_putstr_fd("Error: empty command\n", 2);
        exit(127);
    }

    args = ft_split_args(cmd);
    if (!args || !args[0])
    {
        ft_putstr_fd("Error: invalid command\n", 2);
        if (args)
            ft_free_split(args);
        exit(127);
    }

    cmd_path = get_command_path(args[0], envp);
    if (!cmd_path)
    {
        ft_putstr_fd("Command not found: ", 2);
        ft_putstr_fd(args[0], 2);
        ft_putstr_fd("\n", 2);
        ft_free_split(args);
        exit(127);
    }

    printf("CMD PATH: %s\n", cmd_path);

    if (execve(cmd_path, args, envp) == -1)
    {
        perror("execve");
        free(cmd_path);
        ft_free_split(args);
        exit(1);
    }
    // Este exit nunca se ejecutará si execve funciona
    exit(1);
}

void pipex(char **argv, char **envp, int infile, int outfile)
{
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) // Child 1
    {
        dup2(infile, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execute(argv[2], envp);
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) // Child 2
    {
        dup2(fd[0], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execute(argv[3], envp);
    }

    // Parent process
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
