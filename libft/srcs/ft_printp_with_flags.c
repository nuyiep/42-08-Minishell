/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp_with_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:13:18 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_pf(unsigned long string_addr, t_flags *flags, int *wc)
{
	char	*n;
	int		len;

	n = ft_ultoa_base(string_addr);
	len = 0;
	if (flags->neg == 0 && (flags->dot == 1 && flags->prec == 1)
		&& flags->width > flags->prec)
	{
		if (flags->prec < (int)ft_strlen(n))
			len += print_dupe(' ', flags->width - (int)ft_strlen(n));
		else
			len += print_dupe(' ', flags->width - flags->prec);
		flags->width -= len;
	}
	*wc += len;
	wc += print_dupe('0', flags->prec - (int)ft_strlen(n));
	if (flags->dot == 1)
		flags->d = ' ';
	if (flags->dot == 1 && flags->width == 0)
		flags->width = flags->prec;
	if (flags->dot == 1 && (flags->prec < (int)ft_strlen(n)) && n[0 != '0'])
		flags->prec = (int)ft_strlen(n);
	print_stonf(n, flags, wc);
	free(n);
}
