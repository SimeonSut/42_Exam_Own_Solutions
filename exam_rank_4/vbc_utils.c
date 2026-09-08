+/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:56:55 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/07 14:09:17 by ssutarmi         ###   ########.fr       */
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
	{
		free(new);
		return (NULL);
	}
	new->str[len] = NULL;
	while (i < len)
	{
		new->str[i] = str[start];
		i++;
		start++;
	}
	new->right = NULL;
	new->left = NULL;
	return (0);
}

