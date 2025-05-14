/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 12:00:32 by aarcos            #+#    #+#             */
/*   Updated: 2025-04-11 12:00:32 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PROOBAR POR SEPARADO!!!

#include "pipex.h"

char *get_command_path(char *cmd, char **envp)
{
    int     i = 0;
    char    **paths;
    char    *path_env = NULL;
    char    *cmd_path;
    char    *full_path;

    // ¿Está listo el chorizo?
    if (access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    // Localiza la ristra
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
            i++;
    
    if (!envp[i])
        return (NULL);
    
    path_env = envp[i] + 5;
    
    paths = ft_split_colon(path_env);
    if (!paths)
        return (NULL);

    i = 0;
    while (paths[i])
    {
        cmd_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(cmd_path, cmd);
        free(cmd_path);

        if (access(full_path, X_OK) == 0)
        {
            ft_free_split(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    ft_free_split(paths);
    return (NULL);
}