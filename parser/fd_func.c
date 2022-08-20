/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:00:44 by tanya             #+#    #+#             */
/*   Updated: 2022/08/20 17:29:49 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	file_descriptors(t_cmd_data *cmds)
{
	int	end[2];

	pipe(end);
	if (cmds[0].fd_in_out[WRITE_FD] == STDOUT_FILENO)
		cmds[0].fd_in_out[WRITE_FD] = end[WRITE_FD];
	else
		close(end[WRITE_FD]);
	if (cmds[1].fd_in_out[READ_FD] == STDIN_FILENO)
		cmds[1].fd_in_out[READ_FD] = end[READ_FD];
	else
		close(end[READ_FD]);
	if (cmds[0].fd_close[0] == -1)
		cmds[0].fd_close[0] = cmds[1].fd_in_out[READ_FD];
	else
		cmds[0].fd_close[1] = cmds[1].fd_in_out[READ_FD];
	if (cmds[1].fd_close[0] == -1)
		cmds[1].fd_close[0] = cmds[0].fd_in_out[WRITE_FD];
	else
		cmds[1].fd_close[1] = cmds[0].fd_in_out[WRITE_FD];
}

void	cmd_fd(t_cmd_data *cmds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((size != 1) && (i != size - 1))
			file_descriptors(cmds + i);
		if (i == size - 1 && (size != 1))
			cmds[i].fd_close[0] = cmds[i - 1].fd_in_out[WRITE_FD];
		i++;
	}
}
