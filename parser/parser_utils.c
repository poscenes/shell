/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:50:48 by mslyther          #+#    #+#             */
/*   Updated: 2022/08/20 16:49:32 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}

int	special_symbol(char *line)
{
	int	ret;

	if (ft_isspace(*line))
		return (1);
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "|", 1))
		return (3);
	if (!ft_strncmp(line, "&&", 2))
		return (4);
	if (!*line)
		return (0);
	ret = ft_isredirect(*line, *(line + 1));
	if (ret == 1 || ret == 2)
		return (5);
	if (ret == 3 || ret == 4)
		return (6);
	return (0);
}

void	add_str(char *line, int *i, int *start, char ***line_split)
{
	int	len;

	len = arr_size(*line_split);
	*line_split = ft_realloc(*line_split,
			sizeof(char *) * len, sizeof(char *) * (len + 2));
	(*line_split)[len] = ft_substr(line, *start, *i - *start);
	*start = *i;
}

void	line_shift(char *line, int i, int shift)
{
	int	len;

	len = ft_strlen(line);
	while (i + shift - 1 < len)
	{
		line[i] = line[i + shift];
		i++;
	}
}

int	check_size(char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (line[i] && ft_strncmp(line[i], "||", 2)
		&& ft_strncmp(line[i], "&&", 2))
	{
		if (!ft_strncmp(line[i], "|", 1))
			count++;
		i++;
	}
	return (count);
}
