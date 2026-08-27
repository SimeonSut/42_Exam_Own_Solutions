/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:19:55 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/07/29 15:08:36 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_queens.h"

void	print_solution(int *pos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		fprintf(stdout, "%d", pos[i]);
		i++;
		if (i < n)
			fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
}

int	is_valid(int col_pos, int row_pos, int *pos)
{
	int	row_i;

	if (row_pos == 0)
		return (0);
	row_i = row_pos;
	while (--row_i >= 0)
	{
		if (pos[row_i] == col_pos)
			return (1);
		if (pos[row_i] == col_pos - (row_pos - row_i))
			return (1);
		if (pos[row_i] == col_pos + (row_pos - row_i))
			return (1);
	}
	return (0);
}

void	n_queens(int col, int row, int n, int *pos)
{
	int	col_i;

	while (row < n)
	{
		col_i = col;
		while (row < n && col_i < n)
		{
			if (is_valid(col_i, row, pos) == 0)
			{
				pos[row] = col_i;
				row++;
				col_i = 0;
				continue ;
			}
			col_i++;
		}
		if (row == 0)
			return ;
		else if (row < n && col_i == n)
		{
			n_queens(pos[row - 1] + 1, row - 1, n, pos);
			break ;
		}
		else if (row < n)
			row++;
		if (row == n)
		{
			print_solution(pos, n);
			row--;
			col = pos[row] + 1;
		}
	}
}

int main(int argc, char **argv)
{
	int	i;
	int	n;
	int	*pos;

	if (argc != 2)
		return (1);
	i = 0;
	n = atoi(argv[1]);
	pos = malloc(n * sizeof(int));
	if (!pos)
		return (1);
	while (i < n)
		pos[i++] = -1;
	n_queens(0, 0, n, pos);
	free(pos);
	return (0);
}
