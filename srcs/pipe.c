

/*
#include "minishell.h"

int count_pipes(t_token *token)
{
	t_token *list;
	int count_process;

	count_process = 0;
	list = token;
	printf("value list->type %d\n", list->type);
	while (list && list->type == TOKEN_PIPE)
	{
		printf("valid loop\n");
		count_process++;	
		printf("number of pipes %d\n", count_process);
		list = list->next;
	}
	printf("end number %d\n", count_process);
	return (count_process);
}
*/
