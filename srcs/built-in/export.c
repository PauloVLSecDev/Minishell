/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:14:59 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/09 19:09:40 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_export()
// {
    
// }
// void ft_export(char **args)
// {
// 	t_env	*name_export;
//  	t_env	*copy_env;
// 	int		i;

//  	i = 1;
// 	name_export = get_shell()->env;
// 	if (!args[1])
// 	{
// 		print_export();
// 		return (0);
// 	}
// 	else
// 	{
// 		while (args[i])
// 		{
// 			if (!ft_strcmp(args[i], get_env_name(name_export)))
// 			{
// 				name_export->content = args[i];
// 			}
// 			i++;
// 		}
// 	}
// }

static void	ft_swap_str(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_env_array(char **array, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
				ft_swap_str(&array[i], &array[j]);
			j++;
		}
		i++;
	}
	printf("DEBUG :aaaaaa\n");
}

void print_export(void)
{
	char	**temp;
	size_t		i;

	i = 0;
	temp = recreate_env(get_shell()->env);
	while (temp[i])
	{
		// sort_env_array(temp, i);
		ft_printf("declare - x %s\n", temp[i]);
		i++;
	}
	free_all(temp);
}


// void print_export(void)
// {
//     t_env *node = get_shell()->env;
	
// 	node->exported = recreate_env(node);
//     while (node)
//     {
//         while (node->exported)
//         {
//             // Imprime: declare -x NAME[="value"]
//             printf("declare -x %s", node->name);
//             if (node->content)
//                 printf("=\"%s\"", node->content);
//             printf("\n");
//         }
//         node = node->next;
//     }
// }

static int	is_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0] || ft_isdigit(name[0]))
	{
		printf("deu erro");
		return 0;
	}
	return 1;
}

 static void ft_error_export(char *name)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}


int ft_export(char **args)
{
	char	*name;
	char	*value;
    int		i;
	char	*equal;
	
	i = 1;
	name = NULL;
	value = NULL;
	sort_env_array(args, i);
    if (!args[1])
    {
		print_export();
        return 1;
    }
    while (args[i])
    {
		equal = ft_strchr(args[i], '=');
        if (equal)
        {
            name = ft_substr(args[i], 0, equal - args[i]);
            value = ft_strdup(equal + 1);
        }
        else
        {
            name = ft_strdup(args[i]);
            value = NULL;
        }
        if (!is_valid_identifier(name))
        {
            ft_error_export(name);
            free(name);
            free(value);
            return (1);
        }
        free(name);
        free(value);
        i++;
    }
	return (0);
}
