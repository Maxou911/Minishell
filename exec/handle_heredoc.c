/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:31:58 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/07/28 23:52:07 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_heredoc_pipe(int *heredoc_pipe)
{
	if (pipe(heredoc_pipe) == -1)
		return (perror("pipe heredoc_pipe"), 1);
	g_signal = SIG_HEREDOC;
	return (0);
}

int	read_heredoc_line(t_redir_type *redir, int write_fd)
{
	char	*line;

	ft_putstr_fd("> ", 1);
	line = get_next_line(0, 0);
	if (!line || g_signal == SIG_INTERRUPT)
	{
		free(line);
		return (1);
	}
	if (ft_strncmp(line, redir->file, ft_strlen(redir->file)) == 0
		&& line[ft_strlen(redir->file)] == '\n')
	{
		free(line);
		return (1);
	}
	ft_putstr_fd(line, write_fd);
	free(line);
	return (0);
}

int	read_heredoc_input(t_redir_type *redir, int write_fd)
{
	while (1)
	{
		if (g_signal == SIG_INTERRUPT)
			break ;
		if (read_heredoc_line(redir, write_fd))
			break ;
	}
	return (0);
}

int	handle_heredoc_child_process(t_redir_type *redir, int *heredoc_pipe)
{
	set_signals_heredoc_child();
	g_signal = SIG_HEREDOC;
	close(heredoc_pipe[0]);
	read_heredoc_input(redir, heredoc_pipe[1]);
	close(heredoc_pipe[1]);
	exit(0);
}

int	handle_heredoc_parent_process(t_exec *exec, int *heredoc_pipe, pid_t pid)
{
	int	status;

	close(heredoc_pipe[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(heredoc_pipe[0]);
		exec->last_exit_status = 128 + SIGINT;
		return (1);
	}
	exec->infile = heredoc_pipe[0];
	return (0);
}
