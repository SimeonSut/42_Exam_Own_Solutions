/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:18:14 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/04 17:18:57 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	*make_set(char **argv, int len)
{
	int	i;
	int *set;

	i = 0;
	set = malloc (len * sizeof(int));
	if (!set)
		return (NULL);
	while (i < len)
	{
		if (argv)
			set[i] = atoi(argv[i]);
		else
			set[i] = 1;
		i++;
	}
	return (set);
}

void	try_n_print(int *set, int *subset, int len, int n)
{
	int	i;
	int	check;
	int	sum;

	i = len;
	check = 0;
	sum = 0;
	while (--i >= 0)
	{
		if (subset[i] == 1)
			sum += set[i];
	}
	while (sum == n && ++i < len)
	{
		if (subset[i] == 1 && check == 0)
		{
			check = 1;
			printf("%d", set[i]);
		}
		else if (subset[i] == 1 && check == 1)
			printf(" %d", set[i]);
	}
	if (sum == n)
		printf("\n");
}

void	powerset(int *set, int *subset, int len, int n)
{
	int	i;

	i = len;
	try_n_print(set, subset, len, n);
	while (--i >= 0)
	{
		if (subset[i] == 0)
			subset[i] = 1;
		else
		{
			subset[i] = 0;
			break ;
		}
	}
	if (i < 0)
		return ;
	powerset(set, subset, len, n);
}

int main(int argc, char **argv)
{
	int		n;
	int		len;
	int		*set;
	int		*subset;

	if (argc < 2)
		return (1);
	n = atoi(argv[1]);
	argv += 2;
	len = argc - 2;
	set = make_set(argv, len);
	if (!set)
		return (1);
	subset = make_set(NULL, len);
	if (!subset)
		return (1);
	powerset(set, subset, len ,n);
	return (0);
}
