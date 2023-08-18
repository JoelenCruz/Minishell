/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ai <jede-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:29:18 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/10 16:09:15 by jede-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//* Vai iniciar o prompt para correr o programa
void	init_prompt(t_main	*main, char **envp)
{
	char		*input;
	const char	*prompt;

	prompt = "\033[1;31mminihell😈--> \033[1;0m";
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			break;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			printf("exit\n");
			break;
		}
		add_history(input);
		init_main(main, input);
		set_env_list(main, envp);
		lexer(main);
		if (main->quotes.error == 0) 
			test_exec(main);
		free(input);
	}
}

//* Funcao main do nosso programa
int	main(int argc, char **argv, char **envp)
{
	t_main	main;

	(void)argc;
	(void)argv;
	init_prompt(&main, envp);
	//tratar aspas
	//lexer
	//se nao tiver carecteres expeciais vai logo para a exec_cmd;
	//analise sintatica --> se for falso da ERRO
	//AST
	//init_exec
}
