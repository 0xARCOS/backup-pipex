#include <stdio.h>
#include "pipex.h"

int main(void)
{
    char *cmd = "cut -d ' ' -f2";
    char **args = ft_split_args(cmd);
    int i = 0;

    while (args && args[i])
    {
        printf("arg[%d] = '%s'\n", i, args[i]);
        i++;
    }
    ft_free_split(args);
    return 0;
}
