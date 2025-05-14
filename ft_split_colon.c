#include <stdlib.h>
#include "pipex.h"

static int count_paths(const char *s)
{
    int count = 0;
    int in_path = 0;

    while (*s)
    {
        if (*s != ':' && in_path == 0)
        {
            in_path = 1;
            count++;
        }
        else if (*s == ':')
            in_path = 0;
        s++;
    }
    return count;
}

static int path_len(const char *s)
{
    int len = 0;
    while (s[len] && s[len] != ':')
        len++;
    return len;
}

char **ft_split_colon(const char *s)
{
    char **paths;
    int i = 0;
    int len;

    if (!s)
        return NULL;

    paths = malloc(sizeof(char *) * (count_paths(s) + 1));
    if (!paths)
        return NULL;

    while (*s)
    {
        while (*s == ':')
            s++;
        if (*s)
        {
            len = path_len(s);
            paths[i] = ft_strndup(s, len);
            if (!paths[i])
            {
                ft_free_split(paths);
                return NULL;
            }
            s += len;
            i++;
        }
    }
    paths[i] = NULL;
    return paths;
}
