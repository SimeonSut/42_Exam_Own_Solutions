/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/10 17:42:40 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int		extend_tree(t_list *lst, int operator, int i)
{
	int	len;

	len = my_strlen(lst->str);
	lst->left = new_node(lst->str, 0, i);
	if (!lst->left)
		return (1);
	lst->right = new_node(lst->str, (i + 1), (len - i + 1));
	if (!lst->right)
		return (1);
	free(lst->str);
	lst->str = malloc(2 * sizeof(char));
	if (!lst->str)
		return (1);
	lst->str[0] = operator;
	lst->str[1] = '\0';
	return (0);
}

void	vbc(t_list *lst, char operator)
{
	int	i;

	i = 0;
	while (lst->str[i])
	{
		if (lst->str[i] == '(')
			while (lst->str[i] && lst->str[i] != ')')
				i++;
		if (!lst->str[i])
			return ;//unexpected end of line
		if (lst->str[0] == '(' && lst->str[i] == ')' && i == my_strlen(lst->str))
			lst->str = quote_trim(lst->str);
		if (lst->str[i] == operator)
		{
			if (extend_tree(lst, operator, i) == 1)
				return ;//malloc or syntax error, free and return
			vbc(lst->left, '+');
			vbc(lst->right, '+');
		}
		i++;
	}
	if (!lst->str[i] && operator == '+')
		vbc(lst, '*');
}

int	calculate(t_list *lst)
{
	int	result;

	result = 0;
	if (!lst->left && !lst->right)
		return (lst->str[0] - 48);
	result = calculate(lst->left);
	if (lst->str[0] == '+')
		result += calculate(lst->right);
	else if (lst->str[0] == '*')
		result *= calculate(lst->right);
	return (result);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	int		result;
	int		len;

	if (argc != 2)
		return (1);
	len = my_strlen(argv[1]);
	lst = new_node(argv[1], 0, len);
	if (!lst)
		return (1);
	vbc(lst, '+');
	result = calculate(lst);
	printf("result is : %d\n", result);
	return (0);
}
