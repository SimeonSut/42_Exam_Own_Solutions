/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 11:46:14 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/08/12 17:25:08 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void		n_queens(int n, int *table, int col, int row);
static int		test_validity(int *table, int n, int col, int row);

int main(int argc, char **argv)
{
	int n;
	int *table;
	
	if (argc < 2)
		return (1);
	n = atoi(argv[1]);
	table = malloc(n * sizeof(int));
	if (!table)
		return (1);
	while (n >= 0)
		table[n--]= -1;
	n = atoi(argv[1]);
	n_queens(n, table, 0, 0);
	return (0);
}

static void	n_queens(int n, int *table, int col, int row)
{
	while (row < n)
	{
		table[col] =row;
		if(test_validity(table, n, col, row) == 0)
		{
			col++;
			if(col == n)
			{
				n_queens(n, table, (col - 1), (table[(col - 1)] + 1));
				break ;
			}
			row = 0;
			continue ;
		}
		row++;
	}
	if (row == n && col > 0)
		n_queens(n, table, (col - 1), (table[(col - 1)] + 1));
}

static int		test_validity(int *table, int n, int col, int row)
{
	int	i;
	int	test_col;

	i = -1;
	test_col = col;
	while (--test_col >= 0)
	{
		if (table[test_col] == row)
			return (1);
		else if (table[test_col] == row - (col - test_col))
			return (1);
		else if (table[test_col] == row + (col - test_col))
			return (1);
	}
	if (col == n - 1)
	{
		while (++i < n)
		{
			fprintf(stdout, "%d", table[i]);
			if (i + 1 < n)
				fprintf(stdout, " ");
		}
		fprintf(stdout, "\n");
	}
	return (0);
}
