/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:53:10 by dkreise           #+#    #+#             */
/*   Updated: 2024/01/28 19:27:16 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	in_redir(t_tokens *tokens, t_cmd *cmd, int i)
{
	int	file;
	int	type;

	type = tokens->toks[i]->type;
	file = 0;
	if (type == IN)
		file = open(tokens->toks[i]->value, O_RDONLY);
	else if (type == HEREDOC)
		file = tokens->toks[i]->hd_file;
	// open file protection
	if (file == -1)
	{
		exit_error(tokens->toks[i]->value, NULL, tokens, cmd);
		cmd->exit_code = 1;
	}
	dup2(file, STDIN_FILENO);
	close(file);
	cmd->redir_in_flg = 1;
}

void	out_redir(t_tokens *tokens, t_cmd *cmd, int i)
{
	int	file;
	int	type;

	type = tokens->toks[i]->type;
	file = 0;
	if (type == OUT)
		file = open(tokens->toks[i]->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND_OUT)
		file = open(tokens->toks[i]->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// open file protection
	if (file == -1)
	{
		exit_error(tokens->toks[i]->value, NULL, tokens, cmd);
		cmd->exit_code = 1;
	}
	dup2(file, STDOUT_FILENO);
	close(file);
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

void	pipe_redir(t_tokens *tokens, t_cmd *cmd, int i) 
{
	//dprintf(2, "cmd: %s\n", cmd->args[0]);
	if (!cmd->redir_in_flg && cmd->prev != NULL)
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
			//dprintf(2, "in->pipe\n");
		}
	}
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
		//dprintf(2, "out->pipe\n");
	}
	else if (i == tokens->tok_cnt && !cmd->redir_out_flg)
	{
		dup2(tokens->initfd[1], STDOUT_FILENO);
		//dprintf(2, "1->out\n");
	}

}





