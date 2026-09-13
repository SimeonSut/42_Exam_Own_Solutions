/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/13 13:44:35 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int		check_validity(char *str)
{
	int	i;
	int	balance;

	i = 0;
	balance = 0;
	while (str[i])
	{
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
			balance--;
		else if (isdigit(str[i]) == 0)
			break ;
		if (balance < 0)
			break ;
		i++;
	}
	if (!str[i] && balance > 0)
		return (printf("Unexpected end of input"), 1);
	if (str[i] && !str[i + 1] && isdigit(str[i]) == 0)
		return (printf("Unexpected end of input"), 1);
	else if (str[i] && str[i + 1] && isdigit(str[i]) == 0)
		return (printf("Unexpected token %c", str[i]), 1);
	return (0);
}

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

int		vbc(t_list *lst, char operator)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	if (quote_trim_check(lst) == 1)
		return (1);
	while (lst->str[i])
	{
		if (lst->str[i] == '(')
			quotes++;
		else if (lst->str[i] == ')')
			quotes--;
		if (quotes == 0 && lst->str[i] == operator)
		{
			if (extend_tree(lst, operator, i) == 1)
				return (1);//malloc or syntax error, free and return
			if (vbc(lst->left, '+') == 1 || vbc(lst->right, '+') == 1)
				return (1);
		}
		i++;
	}
	if (!lst->str[i] && operator == '+')
		return (vbc(lst, '*'));
	return (0);
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
	if (check_validity(argv[1]) == 1)
		return (1);
	len = my_strlen(argv[1]);
	lst = new_node(argv[1], 0, len);
	if (!lst)
		return (1);
	if (vbc(lst, '+') == 1)
		return (1);
	result = calculate(lst);
	printf("result is : %d\n", result);
	return (0);
}
