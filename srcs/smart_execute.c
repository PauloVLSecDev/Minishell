

#include "minishell.h" 

void	smart_execute(t_cmd *cmd)
{
	if (cmd->next == NULL)
	{
		if (is_builtin(cmd->args) != -1)
			exec_builtin(is_builtin(cmd->args), cmd);
		else 
		{
			exec_single_command(cmd);
		}
	}
	else if (cmd->next != NULL)
		execute_pipeline(cmd);
	else 
		return ;
}

void	exec_single_command(t_cmd *cmd)
{
	pid_t pid;
	char **path;
	char **new_env;
	int	status;

	new_env = recreate_env(get_shell()->env);
	path = find_path(get_shell()->env);
	if (!path)
	{
		get_shell()->exit_status = 1;
		exit (get_shell()->exit_status);
	}
	pid = fork();
	if (pid == 0)
	{
		exec_external(cmd, new_env, path);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else 
		return ;
}
