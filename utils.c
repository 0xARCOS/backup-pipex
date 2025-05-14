/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 12:01:22 by aarcos            #+#    #+#             */
/*   Updated: 2025-04-11 12:01:22 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//-----------------------------------------------------------------------------------------
//                          STRNCMP
int ft_strncmp(char const *s1, char const *s2, size_t n)
{
    size_t i = 0;

    if (n == 0)
        return (0);
    while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
//----------------------------------------------------------------------------------------
//                          PUTSTR_FD
void ft_putstr(char *s, int fd)
{
    int i = 0;

    if (!s)
        return;
    while (s[i])
    {
        write(fd, &s[i], 1);
        i++;
    }
}
//----------------------------------------------------------------------------------------
//                          STRLEN
int ft_strlen(char const *s)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

//-------------------------------------------------------------------------------------------------
void ft_free_split(char **arr)
{
    int i = 0;

    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}
//--------------------------------------------------------------------------------------------
//                                      STRJOIN
char *ft_strjoin(char const *s1, char *s2)
{
    int i = 0;
    int j = 0;

    char *copy = (char *)malloc(sizeof(char) * ((ft_strlen(s1)) + (ft_strlen(s2)) + 1));
    if (!copy)
        return NULL;
    
    while (s1[i])
    {
        copy[i] = s1[i];
        i++;
    }

    while (s2[j])
    {
        copy[i + j] = s2[j];
        j++;
    }
    copy[i + j] = '\0';
    return copy;
}
//--------------------------------------------------------------------------------------------
//                                      STRDUP

char *ft_strdup(const char *s1)
{
    char *copy;
    int i = 0;

    copy = malloc(ft_strlen(s1) + 1);
    if (!copy)
        return (NULL);
    while (s1[i])
    {
        copy[i] = s1[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}

//---------------------------------------------------------------------------------------------
//                                    ft_execvp()  

// int ft_execvp(cmd, argv, envp)
// {
//     char *path_value;
//     char *paths;

//     if (strchr(cmd, '/'))
//     {
//         if (access(cmd, X_OK) == 0)
//             execve(cmd, argv, envp);
//         else
//             perror("Command not found");
//     }

//     path_value = get_env("PATH", envp);

//     if (path_value == NULL)
//         perror("PATH not set");
    
//     paths = split(path_value, ':');
//----------------------------------------------------------------------------------------------
//                                     ft_strrchr
//-------------------------------------------------------------
//                      error_open / error_cmd

void error_open(const char *path)
{
    //ft_putstr_fd("pipex: ", 2);
    perror(path);
    exit(1);
}

void error_cmd(const char *cmd)
{
    ft_putstr_fd("pipex: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found\n", 2);
    exit(127);
}

//-----------------------------------------------------------------------------
//              ft_putstr_fd

void ft_putstr_fd(const char *s, int fd)
{
    if (!s)
        return;
    write(fd, s, ft_strlen(s));
}

//                 ft_strndup

char *ft_strndup(const char *s, int len)
{
    char *copy = malloc(len + 1);
    int i = 0;
    if (!copy)
        return NULL;
    while (i < len && s[i])
    {
        copy[i] = s[i];
        i++;
    }
    copy[i] = '\0';
    return copy;
}
