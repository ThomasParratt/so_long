/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:57:05 by tparratt          #+#    #+#             */
/*   Updated: 2024/02/20 17:20:24 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *next_str)
{
	int		count;

	count = 0;
	if (next_str == NULL)
	{
		count += write(1, "(null)", 6);
		if (count < 0)
			return (-1);
	}
	else
	{
		while (*next_str)
		{
			count += write(1, &(*next_str), 1);
			if (count < 0)
				return (-1);
			next_str++;
		}
	}
	return (count);
}
