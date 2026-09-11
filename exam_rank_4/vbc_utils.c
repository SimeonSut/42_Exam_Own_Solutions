/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:56:55 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/11 17:10:06 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int		my_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
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

t_list	*new_node(char *str, int start, int len)
{
	int		i;
	t_list	*new;

	i = 0;
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->str = malloc(len + 1 * sizeof(char));
	if (!new->str)
		return (free(new), NULL);
	new->str[len] = '\0';
	while (i < len)
		new->str[i++] = str[start++];
	new->right = NULL;
	new->left = NULL;
	return (new);
}
