
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

static void	print_args_debug(char **args)
{
	int i;
	char idx;

	i = 0;
	while (args[i])
	{
		write(2, "arg[", 5);
		idx = '0' + i;
		write(2, &idx, 1);
		write(2, "] = '", 5);
		write(2, args[i], ft_strlen(args[i]));
		write(2, "'\n", 2);
		i++;
	}
}

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	if (!cmd || !*cmd)
		error_cmd("empty command");
	args = ft_split_args(cmd, ' ');
	if (!args || !args[0])
		error_cmd("invalid command");
	print_args_debug(args);
	cmd_path = get_command_path(args[0], envp);
	if (!cmd_path)
		error_cmd(args[0]);
	if (execve(cmd_path, args, envp) == -1)
	{
		perror("execve");
		free(cmd_path);
		ft_free_split(args);
		exit(1);
	}
}

static void	child_process(char *cmd, int input, int output, char **envp)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	execute(cmd, envp);
}

void	pipex(char **argv, char **envp, int infile, int outfile)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		perror("pipe"), exit(1);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0]);
		child_process(argv[2], infile, fd[1], envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		child_process(argv[3], fd[0], outfile, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
