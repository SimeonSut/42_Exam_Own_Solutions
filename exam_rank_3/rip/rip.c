/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:57:14 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/12 01:06:12 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

static void	setup(char *str, int len);
static void	rip(char *str, int *array, int len, int count_zero);
static int	move_zeros(int *array, int len, int *iteration);
static int	test_validity(char *str, int *array);

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

static void	setup(char *str, int len)
{
	int	i;
	int	array[len];

	i = 0;
	while (i < len)
		array[i++] = 1;
	if (test_validity(str, array) == 0)
		return ;
	rip(str, array, len, 0);
}

static void	rip(char *str, int *array, int len, int recursion)
{
	int	i;
	int	iteration;
	int	is_valid;

	i = len;
	while (--i > recursion)
		array[i] = 1;
	while (--i >= 0)
		array[i] = 0;
	iteration = 0;
	is_valid = 1;
	while (move_zeros(array, len, &iteration) == 0 || i < len)
	{
		i = recursion + iteration++;
		while (i < len)
		{
			array[i] = 0;
			if (test_validity(str, array) == 0)
				is_valid = 0;
			array[i] = 1;
			i++;
		}
	}
	if (is_valid == 1)
		rip(str, array, len, recursion + 1);
}

static int	move_zeros(int *array, int len, int *iteration)
{
	int	i;
	int count;

	if (*iteration == 0)
		return (0);
	i = len - 1;
	count = 0;
	while (i >= 0 && array[i] == 0)
	{
		array[i--] = 1;
		count++;
	}
	while (i >= 0 && array[i] == 1)
		i--;
	if (i < 0)
		return (1);
	array[i++] = 1;
	if (*iteration >= len - 1)
		*iteration = i;
	array[i++] = 0;
	while (count-- > 0)
		array[i++] = 0;
	return (0);
}

static int	test_validity(char *str, int *array)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (array[i] == 1 && str[i] == '(')
			count++;
		if (array[i] == 1 && str[i] == ')')
			count--;
		if (count < 0)
			return (1);
	}
	if (count > 0)
		return (1);
	i = -1;
	while (str[++i])
	{
		if (array[i] == 1)
			write(1, &str[i], 1);
		else
			write(1, " ", 1);
	}
	return (write(1, "\n", 1), 0);
}
