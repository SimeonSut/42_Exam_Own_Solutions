/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:44:18 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/07 13:47:38 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"

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

int main(int argc, char **argv)
{
	char	*input;
	char	*output;

	if (argc != 2)
		return (1);
	input = argv[1];
	output = quote_trim(input);
	printf("%s\n", output);
	return (0);
}