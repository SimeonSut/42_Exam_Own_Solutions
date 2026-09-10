/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:56:55 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/10 17:09:59 by ssutarmi         ###   ########.fr       */
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

char	*quote_trim(char *str)
{
	int		len;
	int		i;
	char	*new;

	len = my_strlen(str);
	if (str[0] != '(' || str[len - 1] != ')')
		return (str);
	i = 0;
	len -= 2;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while(i < len)
	{
		new[i] = str[i + 1];
		i++;
	}
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
