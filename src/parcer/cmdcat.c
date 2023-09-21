/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:57:47 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/19 17:57:47 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_first_cmd(t_node *aux, int size)
{
	int counter;

	counter = 0;
	while(counter++ < size)
	{
		if(aux->token.type == STRING)
			return (aux->index);
		aux = aux->next;
	}
	return (-1);
}

char	**copy_first_cmd(t_lexer tokens, int index)
{
	int	counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter++ < index)
		aux = aux->next;
	return (ft_arrdup(aux->token.arr));
}

t_node *create_n_cmd(char **temp)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.arr = ft_arrdup(temp);
	ft_free_array(&temp);
	new->token.type = STRING;
	return(new);
}

void	insert_temp(t_lexer *tokens, int index, char **temp)
{
	t_node *new;

	remove_node(tokens, index);
	new = create_n_cmd(temp);
	insert_node(tokens, new, index);
}

void	cmdpipecat(t_lexer *tokens, t_node *aux, int index)
{
	char **temp;
	int aux_index;
	bool cmdcat;

	temp = copy_first_cmd(*tokens, index);
	aux = aux->next;
	while(aux->token.type != PIPE && aux != tokens->head)
	{
		if(aux->token.type == STRING && aux->index != index)
		{
			aux_index = aux->index;
			temp = ft_arrjoin(temp, aux->token.arr);
			remove_node(tokens, aux->index);
			aux = find_node(*tokens, aux_index);
			cmdcat = true;
		}
		else
			aux = aux->next;
	}
	if (cmdcat)
		insert_temp(tokens, index, temp);
}

//*Esta função junta os tipos S todos no mesmo nó, para que entre pipes só haja um tipo S
void	cmdcat(t_lexer *tokens)
{
	//int	counter;
	t_node *aux;
	int	cmd_index;
	//int	size;

	//counter = 0;
	aux = tokens->head;
	//size = tokens->size;
	while(1)
	{
		cmd_index = find_first_cmd(aux, tokens->size); //*encontra o primeiro comando e devolve o seu index
		ft_printf("cmd index: %d\n", cmd_index);
		if(cmd_index == -1) //*Se não houver cmd, acaba aqui;
			return ;
		cmdpipecat(tokens, aux, cmd_index); //*concatenar os tipo S até ao próximo pipe ou até ao fim da lista
		while(aux->token.type != PIPE && aux->next != tokens->head)
			aux = aux->next;
		if(aux->next == tokens->head)
			break ;
		aux = aux->next;
	}
}
