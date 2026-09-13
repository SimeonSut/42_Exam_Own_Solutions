/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:12:11 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/13 23:43:22 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct	s_list
{
	char			*str;
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

int		check_quotes_validity(char *str)
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
		if (balance < 0)
			break ;
		i++;
	}
	if (str[i] && !str[i + 1] && balance < 0)
		return (printf("Unexpected end of input\n"), 1);
	else if (str[i] && str[i + 1] && balance < 0)
		return (printf("Unexpected token )\n"), 1);
	if (str[i] && !str[i + 1] && balance > 0)
		return (printf("Unexpected end of input\n"), 1);
	else if (str[i] && str[i + 1] && balance > 0)
		return (printf("Unexpected token (\n"), 1);
	return (0);
}

int		check_chars_validity(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			i++;
			continue ;
		}
		if (isdigit(str[i]) == 0 && str[i] != '+' && str[i] != '*' && str[i + 1])
			return (printf("1Unexpected token %c\n", str[i]), 1);
		if (isdigit(str[i]) == 0 && str[i] != '+' && str[i] != '*' && !str[i + 1])
			return (printf("2Unexpected end of input\n"), 1);
		if ((str[i] == '+' || str[i] == '*') && (!str[i + 1]))
			return (printf("3Unexpected end of input\n"), 1);
		i++;
	}
	return (0);
}

char	*quote_trim(char *str, int free_cmd)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = my_strlen(str) - 2;
	if (str[0] != '(' || str[len + 1] != ')')
		return (str);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while(i < len)
	{
		new[i] = str[i + 1];
		i++;
	}
	if (free_cmd == 1)
		free(str);
	return (new);
}

int		quote_trim_check(t_list *lst)
{
	int	i;
	int	len;
	int	count;

	if (lst->str[0] != '(')
		return (0);
	i = 0;
	len = my_strlen(lst->str) - 1;
	count = 0;
	while (lst->str[i])
	{
		if (count == 0 && (i > 0 && i < len))
			return (0);
		if (lst->str[i] == '(')
			count++;
		if (lst->str[i] == ')')
			count--;
		i++;
	}
	lst->str = quote_trim(lst->str, 1);
	if (!lst->str)
			return (1);
	if (quote_trim_check(lst) == 1)
		return (1);
	return (0);
}

t_list	*new_node(char *str, int start, int len)
{
	int		i;
	t_list	*new;

	i = 0;
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->str = malloc((len + 1) * sizeof(char));
	if (!new->str)
		return (free(new), NULL);
	new->str[len] = '\0';
	while (i < len)
		new->str[i++] = str[start++];
	new->right = NULL;
	new->left = NULL;
	return (new);
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
	if (check_quotes_validity((argv[1])) == 1)
		return (1);
	if (check_chars_validity((argv[1])) == 1)
		return (1);
	len = my_strlen(argv[1]);
	lst = new_node(argv[1], 0, len);
	if (!lst)
		return (1);
	if (vbc(lst, '+') == 1)
		return (1);
	result = calculate(lst);
	printf("%d\n", result);
	return (0);
}
