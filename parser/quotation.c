/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:31:38 by mslyther          #+#    #+#             */
/*   Updated: 2022/08/20 17:12:20 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quotation(char *line, int *i, int *flag)
{
	char	q_type;

	q_type = line[*i];
	line_shift(line, *i, 1);
	while (line[*i])
	{
		if (flag && line[*i] == '*')
			*flag = 1;
		if (line[*i] == q_type)
			break ;
		else if ((q_type == '\"') && (line[*i] == '$'))
			line = env_list(line, i);
		(*i)++;
	}
	line_shift(line, *i, 1);
	(*i)--;
	return (line);
}
