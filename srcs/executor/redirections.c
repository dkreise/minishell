/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:53:10 by dkreise           #+#    #+#             */
/*   Updated: 2024/02/04 15:51:47 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	in_redir(t_tokens *tokens, t_cmd *cmd, int i)
{
	int	fd;
	int	type;

	type = tokens->toks[i]->type;
	fd = 0;
	if (type == IN)
		fd = open(tokens->toks[i]->value, O_RDONLY);
	else if (type == HEREDOC)
		fd = tokens->toks[i]->hd_file;
	if (fd == -1)
	{
		exit_error(tokens->toks[i]->value, NULL, tokens, cmd);
		cmd->exit_code = 1;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	cmd->redir_in_flg = 1;
}

void	out_redir(t_tokens *tokens, t_cmd *cmd, int i)
{
	int	fd;
	int	type;

	type = tokens->toks[i]->type;
	fd = 0;
	if (type == OUT)
		fd = open(tokens->toks[i]->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND_OUT)
		fd = open(tokens->toks[i]->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		exit_error(tokens->toks[i]->value, NULL, tokens, cmd);
		cmd->exit_code = 1;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd->redir_out_flg = 1;
}

void	do_redir(t_tokens *tokens, t_cmd *cmd, int i)
{
	int	type;

	type = tokens->toks[i]->type;
	if (type == IN || type == HEREDOC)
		in_redir(tokens, cmd, i);
	else if (type == OUT || type == APPEND_OUT)
		out_redir(tokens, cmd, i);
}

void	pipe_redir_aux(t_cmd *cmd)
{
	if (!cmd->prev->pipe_done_flg)
	{
		pipe(cmd->prev->pipefd);
		cmd->prev->pipe_done_flg = 1;
		close(cmd->prev->pipefd[1]);
	}
	if (cmd->prev->pipe_done_flg)
	{
		dup2(cmd->prev->pipefd[0], STDIN_FILENO);
		close(cmd->prev->pipefd[0]);
	}
}

void	pipe_redir(t_tokens *tokens, t_cmd *cmd, int i)
{
	if (!cmd->redir_in_flg && cmd->prev != NULL)
		pipe_redir_aux(cmd);
	else if (cmd->redir_in_flg && cmd->prev != NULL)
	{
		if (cmd->prev->pipe_done_flg)
			close(cmd->prev->pipefd[0]);
	}
	if (i != tokens->tok_cnt && !cmd->redir_out_flg)
	{
		pipe(cmd->pipefd);
		cmd->pipe_done_flg = 1;
		dup2(cmd->pipefd[1], STDOUT_FILENO);
		close(cmd->pipefd[1]);
	}
	else if (i == tokens->tok_cnt && !cmd->redir_out_flg)
	{
		dup2(tokens->initfd[1], STDOUT_FILENO);
		close(tokens->initfd[1]);
	}
}
