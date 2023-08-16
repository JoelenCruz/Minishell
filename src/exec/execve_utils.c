/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:46:02 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/16 21:56:18 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//COPIA DO PIPEX

void	free_and_exit(int exit_code, char	**command, char	*pathname, int flag)
{
	if (flag == 1)
		ft_free_str(&pathname);
	ft_free_array(&command);
	exit(exit_code);
}

void	error_management(char *str, int stdout_copy, int exit_code)
{
	if (!str)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno));
		exit(exit_code);
	}
	if (stdout_copy == 0)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), str);
		exit(exit_code);
	}
	dup2(stdout_copy, STDOUT_FILENO);
	if (ft_strncmp("/", str, 1))
		ft_printf("pipex: Command not found: %s\n", str);
	else if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3))
		ft_printf("pipex: Command not found: %s\n", str);
	else
		ft_printf ("pipex: %s: %s\n", strerror(errno), str);
}
