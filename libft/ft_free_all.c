/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
<<<<<<<< HEAD:utils/utils.c
/*   Created: 2025/06/02 20:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/04 18:59:33 by brunogue         ###   ########.fr       */
========
/*   Created: 2025/06/04 18:52:26 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/04 18:52:42 by pvitor-l         ###   ########.fr       */
>>>>>>>> 02957d94d4015e5ecf28e4dd5a66dd7042ce8a64:libft/ft_free_all.c
=======
/*   Created: 2025/06/04 18:52:26 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/05 20:41:31 by pvitor-l         ###   ########.fr       */
>>>>>>> dev
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(char **matrix)
{
	int	i;

<<<<<<< HEAD
<<<<<<<< HEAD:utils/utils.c
	node = (t_env *)malloc(sizeof(t_env);
    if (!node)
        return (NULL);
    node->name = name;
    node->content = content;
    node->next = NULL;
    return (node);
}

t_env	*insertion_node_env(char **env)
{
	t_env	*head;
	char	**content_split;

	content_split = ft_split(env, "=");
	if (!content_split)
		return (NULL);
========
=======
>>>>>>> dev
	if (!matrix)
		return ;
	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
<<<<<<< HEAD
>>>>>>>> 02957d94d4015e5ecf28e4dd5a66dd7042ce8a64:libft/ft_free_all.c
=======
>>>>>>> dev
}
