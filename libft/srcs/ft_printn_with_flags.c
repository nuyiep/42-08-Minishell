/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printn_with_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:48:45 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_pointer_space(t_flags *flags, int *wc, char *n)
{
	if (flags->dot == 1 && (flags->prec <= flags->width))
		*wc += print_dupe(flags->d, flags->width - flags->prec);
	else if (flags->dot == 1 && flags->width == 0)
		*wc += print_dupe(flags->d, flags->prec - (int)ft_strlen(n));
	else if (flags->dot == 0)
		*wc += print_dupe(flags->d, flags->width - (int)ft_strlen(n));
}

void	print_stonf(char *n, t_flags *flags, int *wc)
{
	int	i;

	if (n == NULL)
		print_sf("(null)", flags, wc);
	else
	{
		if (flags->neg == 0)
			print_pointer_space(flags, wc, n);
		i = 0;
		while (i < (int)ft_strlen(n))
		{
			if (flags->dot == 1 && i >= flags->prec)
				break ;
			if (n[i] == '%' && n[i + 1] == '%')
				i++;
			ft_putchar_fd(n[i++], 1);
			(*wc)++;
		}
		if (flags->neg == 1)
			print_pointer_space(flags, wc, n);
	}
}

static void	print_number_space(t_flags *flags, int *wc, char *n)
{
	int	len;

	len = 0;
	if (flags->neg == 1 || flags->dot == 0 || flags->prec == 0
		|| flags->prec > flags->width)
		return ;
	if ((int)ft_strlen(n) > flags->prec)
		len += print_dupe(' ', flags->width - (int)ft_strlen(n));
	else if (n[0] == '-')
		len += print_dupe(' ', flags->width - flags->prec - 1);
	else if (n[0] != '-')
		len += print_dupe(' ', flags->width - flags->prec);
	flags->width -= len;
	*wc += len;
}

static void	check_splus(t_flags *flags, int *wc, int n)
{
	if (n >= 0 && flags->spc == 1)
	{
		ft_putchar_fd(' ', 1);
		(*wc)++;
	}
	if (n >= 0 && flags->plus == 1)
	{
		ft_putchar_fd('+', 1);
		(*wc)++;
	}
}

void	print_nf(int n, t_flags *flags, int *wc)
{
	char	*n_string;
	int		i;

	n_string = ft_itoa(n);
	i = 0;
	print_number_space(flags, wc, n_string);
	if (n_string[0] == '-' && (flags->dot == 1 || flags->d == '0')
		&& ++i && ++(*wc))
		ft_putchar_fd('-', 1);
	n_string += i;
	flags->width -= i;
	check_splus(flags, wc, n);
	*wc += print_dupe('0', flags->prec - (int)ft_strlen(n_string));
	if (flags->dot == 1)
	{
		flags->d = ' ';
		if (flags->width == 0)
			flags->width = flags->prec;
		if (flags->prec < (int)ft_strlen(n_string) && n_string[0] != '0')
			flags->prec = (int)ft_strlen(n_string);
	}
	print_stonf(n_string, flags, wc);
	free(n_string - i);
}
