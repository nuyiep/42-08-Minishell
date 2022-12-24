/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printh_with_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:18:02 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_hexstart(t_flags *flags, unsigned int n, int *wc, char *base)
{
	if (flags->hash == 1 && n > 0)
	{
		*wc += 2;
		if (base[10] == 'a')
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
	}
	if (flags->dot == 1)
		flags->d = ' ';
}

void	print_hf(unsigned int n, char *base, t_flags *flags, int *wc)
{
	char	*n_string;
	int		len;

	n_string = ft_uitoa_base(n, base);
	len = 0;
	if (flags->neg == 0 && flags->dot == 1 && flags->prec > 0
		&& (flags->width > flags->prec))
	{
		if ((int)ft_strlen(n_string) > flags->prec)
			len += print_dupe(' ', flags->width - (int)ft_strlen(n_string));
		else
			len += print_dupe(' ', flags->width - flags->prec);
		flags->width -= len;
	}
	print_hexstart(flags, n, wc, base);
	*wc += print_dupe('0', flags->prec - (int)ft_strlen(n_string)) + len;
	if (flags->dot == 1)
	{
		if (flags->width == 0)
			flags->width = flags->prec;
		if (n_string[0] != '0' && (flags->prec < (int)ft_strlen(n_string)))
			flags->prec = (int)ft_strlen(n_string);
	}
	print_stonf(n_string, flags, wc);
	free(n_string);
}
