/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/08 18:37:48 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"


int		extend(t_list *current, int operator, int len, int i)
{
	current->left = new_node(current->str, 0, i);
	if (!current->left)
		return (1);
	current->right = new_node(current->right, i, len - i);
	if (!current->right)
		return (1);
	current->str = realloc(current->str, 1);
	if (!current->str)
		return (1);
	current->str[0] = operator;
	return (0);
}

void	vbc(t_list *lst, t_list *current, char operator, int len)
{
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	while (current->str[i])
	{
		if (current->str[i] == '(')
			inquote++;
		else if (current->str[i] == ')')
			inquote--;
		else if (current->str[i] == operator && inquote == 0)
			extend()
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	int		len;

	if (argc != 2)
		return (1);
	len = my_strlen(argv[1]);
	lst = new_node(argv[1], 0, len);
	if (!lst)
		return (1);
	vbc(lst, lst, '*', len);
	return (0);
}

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
