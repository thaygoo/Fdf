/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_PTF.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:51:27 by huburton          #+#    #+#             */
/*   Updated: 2025/01/21 15:41:59 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex_PTF(unsigned int number, char type)
{
	int	rtn;
	int	tmp;

	rtn = 0;
	if (number >= 16)
	{
		tmp = ft_puthex_PTF(number / 16, type);
		if (tmp < 0)
			return (-1);
		rtn += tmp;
	}
	if (type == 'X')
		tmp = ft_putchar_PTF("0123456789ABCDEF"[number % 16]);
	if (type == 'x')
		tmp = ft_putchar_PTF("0123456789abcdef"[number % 16]);
	if (tmp < 0)
		return (-1);
	return (rtn + 1);
}
