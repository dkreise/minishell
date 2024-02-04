/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:21:25 by rpliego           #+#    #+#             */
/*   Updated: 2024/02/04 16:11:06 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mod_strcmp(char *cmd, char *env)
{
    int i;
    i = 0;
    while (cmd[i] && env[i])
    {
        if (cmd[i] == '=' && env[i] == '=')
            return (TRUE);
        if (cmd[i] != env[i])
            return (FALSE);
        i++;
    }
    if (cmd[i] == '\0' && (env[i] == '\0' || env[i] == '='))
        return (TRUE);
    return (FALSE);
}

int var_exist(char *cmd, t_env *env)
{
    t_env   *temp;
    temp = env;
    while (temp != NULL)
    {
        if (mod_strcmp(cmd, temp->data) == TRUE)
            return (TRUE);
        temp = temp->next;
    }
    return (FALSE);
}

int check_blt(char *cmd)
{
    if (cmd)
    {
        if (ft_strncmp(cmd, "env", 4) == 0)
            return (1);
        if (ft_strncmp(cmd, "export", 7) == 0)
            return (1);
        if (ft_strncmp(cmd, "unset", 6) == 0)
            return (1);
        if (ft_strncmp(cmd, "pwd", 4) == 0)
            return (1);
        if (ft_strncmp(cmd, "cd", 3) == 0)
            return (1);
        if (ft_strncmp(cmd, "exit", 6) == 0)
            return (1);
        if (ft_strncmp(cmd, "echo", 5) == 0)
            return (1);
    }
    return (0);
}

void    exec_blt(t_cmd *cmd_s, t_env *env)
{
    char    **cmd;

    cmd = cmd_s->args;
    if (ft_strncmp(cmd[0], "env", 4) == 0)
        ft_env(env);
    else if (ft_strncmp(cmd[0], "export", 7) == 0)
        ft_export(cmd, &env);
    else if (ft_strncmp(cmd[0], "unset", 6) == 0)
        ft_unset(cmd, &env);
    else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
        ft_pwd();
    else if (ft_strncmp(cmd[0], "cd", 3) == 0)
        cmd_s->exit_code = ft_cd(cmd, env);
    else if (ft_strncmp(cmd[0], "exit", 6) == 0)
        cmd_s->exit_code = ft_exit(cmd);
    else if (ft_strncmp(cmd[0], "echo", 5) == 0)
        ft_echo(cmd);
}