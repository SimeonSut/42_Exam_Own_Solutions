/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/04 18:21:12 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//./vbc '(((2+2)*(2+2)*2+2)*(2+2)*2+2)*2' | cat -e
//./vbc '(3+4)*5' | cat -e
//./vbc '1' | cat -e
//./vbc 2+2*2+2*2+2*2+2*2+2*2
/*
+
2|2*2+2*2+2*2+2*2+2*2
	+
	2*2|2*2+2*2+2*2+2*2
		+
		2*2|2*2+2*2+2*2
		+
		2*2|2*2+2*2
		+
		2*2|2*2



(((2+2)*(2+2)*2+2)*(2+2)*2+2)*2
*
2|((2+2)*(2+2)*2+2)*(2+2)*2+2
*
2+2|((2+2)*(2+2)*2+2)*(2+2)
*
2+2|(2+2)*(2+2)*2+2
*
2+2|(2+2)*2+2
*
2+2|2+2

first, the split by the multiplication happens, the by the addition.
If any function starts by a parenthesis, trim it from then and start on the loop
*/

enum e_modes
{
	INIT = 0,
	NUMBER = 1,
	OPERATION = 2
};

typedef struct	s_list
{
	char	*str;
	struct s_list	*right;
	struct s_list	*left;
}				t_list;

int		my_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char	*quote_trim(char *str)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = (my_strlen(str) - 1);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while(i + 1 < len)
	{
		new[i] = str[i + 1];
		i++;
	}
	return (new);
}

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

int	operation_split(t_list *lst, char *input, char operation)
{
	int	i;
	int	first_len;

	i = 0;
	first_len = 0;
	while (input[i])
	{
	}
}

int	vbc(t_list *lst, char *input, int sum)
{
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
	result = vbc(lst, total_operation, 0);
	return (0);
}
