/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:07:17 by tanya             #+#    #+#             */
/*   Updated: 2022/08/20 16:55:51 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		env_parsing(t_parser_data *data, int *j)
{
	if (data->curr_word[0] == '\0')
		return (1);
	if (*j && data->curr_word[*j - 1] == '$' && data->curr_word[*j])
	{
		line_shift(data->curr_word, *j - 1, 1);
		(*j)--;
		return (0);
	}
	parse_env(data, j);
	return (0);
}

void	parse_env(t_parser_data *data, int *j)
{
	int	index;

	index = 0;
	while (index <= *j)
	{
		while (index <= *j && ft_isspace(data->curr_word[index]))
		{
			line_shift(data->curr_word, 0, 1);
			*j -= 1;
		}
		while (index <= *j && !ft_isspace(data->curr_word[index]))
			index++;
		if (index < *j)
		{
			add_cmd(data->cmds, data->size,
				ft_substr(data->curr_word, 0, index));
			line_shift(data->curr_word, 0, index + 1);
			*j -= index + 1;
			index = 0;
		}
	}
}
