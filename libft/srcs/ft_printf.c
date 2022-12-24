/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:22:30 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_with_format(
	char format, va_list *args, t_flags *flags, int *wc)
{
	if (format == 'c')
		print_cf(va_arg(*args, int), flags, wc);
	else if (format == 's')
		print_sf(va_arg(*args, char *), flags, wc);
	else if (format == 'p')
		print_pf(va_arg(*args, unsigned long), flags, wc);
	else if (format == 'd' || format == 'i')
		print_nf(va_arg(*args, int), flags, wc);
	else if (format == 'u')
		print_unf(va_arg(*args, unsigned int), flags, wc);
	else if (format == 'x')
		print_hf(va_arg(*args, int), "0123456789abcdef", flags, wc);
	else if (format == 'X')
		print_hf(va_arg(*args, int), "0123456789ABCDEF", flags, wc);
	else if (format == '%' && ++(*wc))
		ft_putchar_fd('%', 1);
}

static void	get_format(char format, va_list *args, t_flags *flags, int *wc)
{
	if (flags->zero == 1)
		flags->d = '0';
	print_with_format(format, args, flags, wc);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		wc;
	int		i;
	t_flags	*flags;

	va_start(args, str);
	wc = 0;
	i = -1;
	flags = malloc(sizeof(t_flags));
	if (flags == NULL)
		return (0);
	while (++i < (int)ft_strlen(str))
	{
		default_flag(flags);
		if (str[i] == '%' && ++i)
		{
			get_flags(str, &i, flags);
			get_format(str[i], &args, flags, &wc);
		}
		else
			print_cf(str[i], flags, &wc);
	}
	va_end(args);
	free(flags);
	return (wc);
}
