/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:26 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/24 12:06:23 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	init_quotes(t_quotes *quotes)
{
	quotes->head = NULL;
	quotes->size = 0;
	quotes->counter = 0;
}

void	init_ast(t_ast	*ast)
{
	ast->head = NULL;
	ast->counter = 0;
	ast->size = 0;
}

void	init_lexer(t_lexer *stack)
{
	stack->head = NULL;
	stack->size = 0;
}

void	init_env(t_env *stack)
{
	stack->head = NULL;
	stack->size = 0;
	stack->i = 0;
}
void	init_std(t_std *fd)
{
	fd->stdin = dup(STDIN_FILENO);
	fd->stdout = dup(STDOUT_FILENO);
	fd->stderr = dup(STDERR_FILENO);
}
void    init_bool(t_bool *flags)
{
	flags->put_node_behind = false;
	flags->rdr_treated = false;
	flags->rdr_err = false;
	flags->signal = false;
	flags->not_print = false;
	flags->hd = false;
}

//* Inicia as variaveis da estrutura principal (t_main) que têm que ser iniciadas sempre que se inicia o prompt
// Ou seja, as estruturas relacionadas com o imput
//! Dar free sempre que se inicia novamente
void	init_input(t_main *main, char *input)
{
	main->input_prompt = input;
	init_bool(&main->flags);
	init_quotes(&main->quotes);
	init_lexer(&main->tokens);
	init_ast(&main->ast);
	main->hd.fd = 0;
	main->hd.index = 0;
	main->hd.str = NULL;
}

//* Inicia as variaveis da estrutura principal (t_main) que têm que ser iniciadas apenas uma vez
void	init_main(t_main *main, char **envp)
{
	init_env(&main->env_list);
	init_env(&main->export_list);
	set_env_list(main, envp);
	copy_exp(main);
	main->env_arr = NULL;
	main->path_pwd = NULL;
	main->exit_code = 0;
	main->error = 0;
	main->line = 0;
	init_std(&main->fd); //*É AQUI! Se nao estou a fazer dup(1) e o 1 já foi redirecionado
	main->flags.signal = false;
}
