/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 14:20:49 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/13 15:41:46 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

static void	setup(char *str, int len);
static void	rip(char *str, int *array, int len, int recursion);
static int	move_zeros(int *array, int len, int *iter_start);
static int	test_validity(char *str, int *array);

int 	main(int argc, char **argv)
{
	int len;

	if (argc != 2)
		return 1;
	len = 0;
	while (argv[1][len])
		len++;
	setup(argv[1], len);
	return 0;
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
	int	iter_start;
	int	is_valid;

	i = recursion;
	while (--i >= 0)
		array[i] = 0;
	iter_start = 0;
	is_valid = 1;
	while (move_zeros(array, len, &iter_start) == 0)
	{
		i = recursion + iter_start++;
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

static int		move_zeros(int *array, int len, int *iter_start)
{
	int	i;
	int count;
	
	if (*iter_start == 0)
		return 0;
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
		return 1;
	array[i++] = 1;
	if (*iter_start >= len - 1)
		*iter_start = i;
	array[i++] = 0;
	while (count-- > 0)
		array[i++] = 0;
	return 0;
}

static int		test_validity(char *str, int *array)
{
	int	i;
	int	balance;

	i = -1;
	balance = 0;
	while (str[++i])
	{
		if (array[i] == 1 && str[i] == ')')
			balance--;
		else if (array[i] == 1 && str[i] == '(')
			balance++;
		if (balance < 0)
			return 1;
	}
	if (balance > 0)
		return 1;
	i = -1;
	while (str[++i])
	{
		if (array[i] == 1)
			write(1, &str[i], 1);
		else
			write(1, " ", 1);
	}
	return(write(1, "\n", 1), 0);
}
