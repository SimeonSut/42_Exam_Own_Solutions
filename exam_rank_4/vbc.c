/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/10 11:36:16 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int		extend_tree(t_list *current, int operator, int len, int i)
{
	current->left = new_node(current->str, 0, i);
	if (!current->left)
		return (1);
	current->right = new_node(current->str, (i + 1), (len - i + 1));
	if (!current->right)
		return (1);
	free(current->str);
	current->str = malloc(2 * sizeof(char));
	if (!current->str)
		return (1);
	current->str[0] = operator;
	current->str[1] = '\0';
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
		{
			if (extend_tree(current, operator, len, i) == 1)
				return ;//malloc or syntax error, free and return
			vbc(lst, current->left, '+', i);
			vbc(lst, current->right, '+', len - i);
		}
		i++;
	}
	if (!current->str[i] && operator == '*')
		return ;
	if (!current->str[i] && operator == '+')
		vbc(lst, current, '*', len);
}

int	count_tree(t_list *lst)
{
	int	result;

	result = 0;
	if (lst->left)
		result = count_tree(lst->left);
	if (lst->right)
	{
		if (lst->str[0] == '*')
		
			result *= count_tree(lst->right);
		else if (lst->str[0] == '+')
			result += count_tree(lst->right);
	}
	if (!lst->left && !lst->right)
		result = lst->str[0] - 48;
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
	vbc(lst, lst, '+', len);
	result = count_tree(lst);
	printf("result is : %d\n", result);
	return (0);
}
