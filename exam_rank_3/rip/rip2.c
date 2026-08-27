/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:53:54 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/11 12:55:02 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int 	main(int argc, char **argv)
{
	int		i;
	char	*str;

	if (argc != 2)
		return (1);
	i = 0;
	str = argv[1];
	while (str[i])
		i++;
	setup(str, i);
	return (0);
}

static void	rip(char *str, int *array, int len)
{
	int		i;
	char	tmp;

	if (visit(str, start) == 1 || bfs != 0)
		return ;
	i = start + 1;
	while (str[i])
	{
		tmp = str[i];
		str[i] = ' ';
		rip(str, 0, i);
		str[i] = tmp;
		i++;
	}
	rip(str, 1, start + 1);
}

static int		check_validity(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count--;
		if (count < 0)
			return (1);
		i++;
	}
	if (count > 0)
		return (1);
	puts(str);
	return (0);
}

static int		visit(char *str, int start)
{
	int		i;
	int		validity;
	char	tmp;

	i = start + 1;
	if (check_validity(str) == 0)
		return 1;
	while (str[i])
	{
		tmp = str[i];
		str[i] = ' ';
		validity = check_validity(str);
		str[i] = tmp;
		i++;
	}
	return (validity);
}