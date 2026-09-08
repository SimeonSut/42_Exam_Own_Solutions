/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/07 14:35:56 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int	operation_split(t_list *lst, char *input, char operation)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == operation)
			;
	}
}

int	vbc(t_list *lst, int sum)
{
	return 0;
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	int		result;

	if (argc != 2)
		return (1);
	lst = list_init(argv[1]);
	if (!lst)
		return (1);
	result = vbc(lst, 0);
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
