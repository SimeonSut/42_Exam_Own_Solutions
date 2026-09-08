/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:56:57 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/09/08 14:03:28 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct	s_list
{
	char	*str;
	struct s_list	*right;
	struct s_list	*left;
}				t_list;

int		my_strlen(char *str);
char	*quote_trim(char *str);
t_list	*new_node(char *str, int start, int len);

enum e_modes
{
	INIT = 0,
	NUMBER = 1,
	OPERATION = 2
};

