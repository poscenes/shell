/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:47:55 by mslyther          #+#    #+#             */
/*   Updated: 2022/08/20 16:41:07 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**error_message(char ***line_split, int i)
{
	printf("Syntax error near unexpected token \'%s\'\n",
		(*line_split)[i]);
	free_array(*line_split);
	return (NULL);
}

char	**error_quotes(char ***line_split)
{
	printf("Syntax error: unclosed quote\n");
	free_array(*line_split);
	return (NULL);
}

int	free_if_error(t_cmd_data *comand)
{
	int	i;

	perror("minishell");
	i = 0;
	while (comand[i].cmd_arg != NULL)
	{
		free_array(comand[i].cmd_arg);
		i++;
	}
	free(comand);
	return (0);
}
