/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:33:30 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/05 20:48:08 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*my_strdup(char *str)
{
	int	len;
	char *new;

	len = my_strlen(str);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while (--len >= 0)
		new[len] = str[len];
	return (new);
}

void	permutations(char *str, int start, int len)
{
	int		i;
	char	tmp;
	char	*saved;

	if (start == len)
	{
		write(1, str, len);
		write(1, "\n", 1);
	}
	i = start;
	while (i < len)
	{
		tmp = str[start];
		str[start] = str[i];
		str[i] = tmp;
		saved = my_strdup(str);
		if (!saved)
			return ;
		permutations(str, start + 1, len);
		str = saved;
		i++;
	}
	free(str);
}

int	main(int argc, char **argv)
{
	int		i;
	int		len;
	char	*str;

	if (argc != 2)
		return (0);
	i = 0;
	len = my_strlen(argv[1]);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (1);
	str[len] = '\0';
	while (argv[1][i])
	{
		str[i] = argv[1][i];
		i++;
	}
	permutations(str, 0, len);
	return (0);
}
