/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:52:29 by mslyther          #+#    #+#             */
/*   Updated: 2022/08/20 16:35:29 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_key(char c)
{
	if ((c == '_') || ft_isalnum(c))
		return (1);
	return (0);
}

char	*join_str(char *line, char *env, int *i, int len)
{
	char	*start;
	char	*start_env;
	char	*end;

	start = ft_substr(line, 0, *i);
	end = ft_strdup(line + (*i) + 1 + len);
	start_env = ft_strjoin(start, env);
	free(start);
	free(line);
	line = ft_strjoin(start_env, end);
	free(start_env);
	free(end);
	(*i) += ft_strlen(env) - 1;
	free(env);
	return (line);
}

char	*status_check(char *line, int j, int *i)
{
	if (line[j] == '?')
		line = join_str(line, ft_itoa(g_info.status), i, 1);
	else if (line[j])
		(*i)++;
	return (line);
}

char	*env_list(char *line, int *i)
{
	int		j;
	char	*key;
	int		len;
	char	*env_line;

	j = (*i) + 1;
	if (!is_key(line[j]))
		return (status_check(line, j, i));
	while (line[j] && ft_isalnum(line[j]))
		j++;
	len = j - (*i) - 1;
	key = ft_substr(line, (*i) + 1, len);
	env_line = get_env(key);
	if (!env_line)
	{
		if (!ft_isdigit(key[0]))
			line_shift(line, *i, len - 1);
		line_shift(line, *i, 2);
		(*i)--;
	}
	else
		line = join_str(line, ft_strdup(ft_strchr(env_line, '=') + 1), i, len);
	free(key);
	return (line);
}
