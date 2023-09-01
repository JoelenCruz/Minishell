/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:15:07 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/28 11:48:53 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_pathname(char	*str, char	*str_path, int *flag)
{
	char	*slash_cmd;
	char	**path;
	char	*temp;
	int		i;

	path = ft_split(str_path, ':');
	i = 0;
	while (path[i])
	{
		slash_cmd = ft_strjoin("/", str);
		temp = ft_strjoin(path[i], slash_cmd);
		ft_free_str(&slash_cmd);
		if (access((const char *)temp, F_OK) == 0)
		{
			*flag = 1;
			str = temp;
			break ;
		}
		ft_free_str(&temp);
		i++;
	}
	ft_free_array(&path);
	return (str);
}

char	*find_path(char	*str, char	**envp, int *flag)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			path = envp[i] + 5;
		i++;
	}
	if (path)
		str = create_pathname(str, path, flag);
	return (str);
}

char	*ft_pathname(int *flag, char **envp, char **cmd, t_main *main)
{
	int		len;
	char	*str;

	str = "\0";
	len = ft_strlen(cmd[0]);
	if (len > 3)
	{
		if (!ft_strncmp(".sh", cmd[0] + ft_strlen(cmd[0]) - 3, 3))
		{
			if (!ft_strncmp("./", cmd[0], 2))
			{
				str = cmd[0] + 2;
				return (str);
			}
			error_management(cmd[0], main);
			free_pathname(NULL, 0);
		}
	}
	if (access((const char *)cmd[0], F_OK))
		str = find_path(cmd[0], envp, flag);
	else
		str = cmd[0];
	return (str);
}

void	execution(char **cmd, t_main *main)
{
	char	*pathname;
	int		error;
	int		flag;

	//printf("entra aqui exec \n");
	pathname = ft_pathname(&flag, main->env_arr, cmd, main);
	if (!strncmp("./", cmd[0], 2))
	{
		cmd[0] = cmd[0] + 2;
		error = execve((const char *)pathname, (char **const)cmd, main->env_arr);
		cmd[0] = cmd[0] - 2;
	}
	else
		error = execve((const char *)pathname, (char **const)cmd, main->env_arr);
	if (error == -1)
		error_management(cmd[0], main);
	free_pathname(pathname, flag);
}

void	exec_other_cmd(char **cmd, t_main *main, bool child)
{
	int	pid;
	int exit_status;

	set_env_arr(main);
	if(child)
		execution(cmd, main);
	else
	{
		pid = fork();
		if(pid == 0)
			execution(cmd, main);
		waitpid(pid, &exit_status, 0);
		if (WEXITSTATUS(exit_status) != 0)
			set_exit_code(main, WEXITSTATUS(exit_status));
		else
			set_exit_code(main, 0);
	}
}

