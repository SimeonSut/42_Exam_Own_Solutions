/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/03 19:10:55 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*Find the end of the current quotes and split by
 *Find the first multiplication and split the tree by it
 *If no multiplication, find the first addition and split by it
 *
 *
 *
 *
 */

enum e_modes
{
	INIT = 0,
	NUMBER = 1,
	OPERATION = 2
};

typedef struct	s_list
{
	union
	{
		char	operation;
		int		number;
	};
	struct s_list	*right;
	struct s_list	*left;
}				t_list;

//./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
//./vbc '(3+4)*5' | cat -e
//./vbc '1' | cat -e

t_list	*list_init(int mode, int number, char operation)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (mode == 0)
		new->number = 0;
	else if (mode == 1)
		new->number = number;
	else if (mode == 2)
		new->operation = operation;
	new->right = NULL;
	new->left = NULL;
	return (0);
}

int	vbc(t_list *lst, char *input)
{
	int	i;
	int	open_quote;

	i = 0;
	open_quote = 0;
	while (input[i] && input[i] != '(')
	{
		i++;
	}
	return 0;
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	char	*total_operation;
	int		result;

	if (argc != 2)
		return (1);
	lst = list_init(0, 0, 0);
	if (!lst)
		return (1);
	total_operation = argv[1];
	result = vbc(lst, total_operation);
	return (0);
}
