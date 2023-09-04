/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:34 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/04 19:44:12 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Quando nao tem path anterior, ele retorna um erro: bash: cd: OLDPWD not set (linha 80)*/
char *find_home(char *path, t_main *main) 
{
    char    *home;
    char    *aux;
    char    *current;
    
    if (path[0] == '~') 
    {
        home = getenv("HOME");
        if (home == NULL)
        {
            printf("cd: No such file or directory\n");
            set_exit_code(main, 1);
            return (NULL);
        }
        aux = ft_substr(path, 1, ft_strlen(path) - 1);
        current = ft_strjoin(home, aux);
        free(aux);
        return (current);
    }
    return (ft_strdup(path));
}

char    *prev_dir(char *path)
{
    static char    prev[4096];

    if (ft_strcmp(path, "-") == 0)
    {
        if (prev[0] != '\0')
            return (ft_strdup(prev));
        else
            return (NULL);
    }
    return (ft_strdup(path));
}

int change_dir(char *path) 
{
    if (chdir(path) == 0) 
        return (0);
     else 
     {
        perror("cd");
        return (1);
    }
}

void    cd(char *path, t_main *main, bool child) 
{
    char    *new_path;
    int     dir;
    char    *current;
    
    if (ft_strcmp(path, "-") == 0)
    {
        if (main->prev)
        {
            change_dir(main->prev);
            ft_printf("%s\n", main->prev);
        }
        else
        {
            //MSG DE ERRO
            set_exit_code(main, 1);
        }
    }
    else
    {
        new_path = find_home(path, main);
        current = ft_calloc(sizeof(char), 4096);
        getcwd(current, 4096);
        dir = change_dir(new_path);
        if (dir == 0)
        {
            main->prev = ft_calloc(sizeof(char), ft_strlen(current) + 1);
            ft_strlcpy(main->prev, current, ft_strlen(current) + 1);
            free(new_path);
            free(current);
        }
    }
    if (child)
        exit(0);
	set_exit_code(main, 0);
}