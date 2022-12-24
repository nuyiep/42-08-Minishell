/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:51:42 by maliew            #+#    #+#             */
/*   Updated: 2022/09/29 01:40:48 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ftdpf_char(int fd, char c, t_ftdpf_flags *flags)
{
	int	count;

	count = 0;
	if (!flags->da && flags->wi)
		count += ftdpf_width(fd, flags->wi - 1, ' ');
	count += write(fd, &c, 1);
	if (flags->da && flags->wi)
		count += ftdpf_width(fd, flags->wi - 1, ' ');
	return (count);
}

int	ftdpf_str(int fd, char *s, t_ftdpf_flags *flags)
{
	int		count;
	int		len;
	char	*str;

	count = 0;
	if (s)
		len = ft_strlen(s);
	else
		len = 6;
	if (flags->dt && (flags->pr < len))
		len = flags->pr;
	if (s)
		str = ft_substr(s, 0, len);
	else
		str = ft_substr("(null)", 0, len);
	if (!flags->da && flags->wi)
		count += ftdpf_width(fd, flags->wi - len, ' ');
	ft_putstr_fd(str, fd);
	if (flags->da && flags->wi)
		count += ftdpf_width(fd, flags->wi - len, ' ');
	free(str);
	return (count + len);
}

int	ftdpf_int(int fd, long n, t_ftdpf_flags *f)
{
	int	count;
	int	neg;
	int	len;

	count = 0;
	ftdpf_get_neg(&n, &neg);
	len = ftdpf_get_len_base(n, 10) * !(f->dt && !f->pr && !n);
	if (!f->da && (!f->ze || f->dt) && f->wi)
		count += ftdpf_width(fd, f->wi - neg - ftdpf_max(f->pr, len), ' ');
	if (neg)
		count += write(fd, "-", 1);
	else if (f->pl)
		count += write(fd, "+", 1);
	else if (f->sp)
		count += write(fd, " ", 1);
	if (f->ze && !f->dt && !f->da && f->wi)
		count += ftdpf_width(fd, f->wi - neg - len, '0');
	if (f->dt)
		count += ftdpf_width(fd, f->pr - len, '0');
	if (!(f->dt && !f->pr && !n))
		ftdpf_print_base(fd, n, "0123456789");
	if (f->da && f->wi)
		count += ftdpf_width(fd, f->wi - neg - ftdpf_max(f->pr, len), ' ');
	return (count + len);
}

int	ftdpf_hex(int fd, unsigned long n, t_ftdpf_flags *flags, char *base)
{
	int	count;
	int	len;

	count = 0;
	len = ftdpf_get_len_base(n, 16) * !(flags->dt && !flags->pr && !n);
	if (!flags->da && (!flags->ze || flags->dt) && flags->wi)
		count += ftdpf_width(fd,
				flags->wi - ftdpf_max(flags->pr, len) - flags->ha * 2,
				' ');
	if (flags->ha && n)
		count += write(fd, base, 2);
	if (flags->ze && !flags->dt && !flags->da && flags->wi)
		count += ftdpf_width(fd, flags->wi - len, '0');
	if (flags->dt)
		count += ftdpf_width(fd, flags->pr - len, '0');
	if (!(flags->dt && !flags->pr && !n))
		ftdpf_print_base(fd, n, base + 2);
	if (flags->da && flags->wi)
		count += ftdpf_width(fd,
				flags->wi - ftdpf_max(flags->pr, len) - flags->ha * 2,
				' ');
	return (count + len);
}

int	ftdpf_ptr(int fd, unsigned long n, t_ftdpf_flags *flags, char *base)
{
	int	count;
	int	len;

	count = 0;
	len = ftdpf_get_len_base(n, 16) * !(flags->dt && !flags->pr && !n);
	if (!flags->da && (!flags->ze || flags->dt) && flags->wi)
		count += ftdpf_width(fd,
				flags->wi - ftdpf_max(flags->pr, len) - 2,
				' ');
	count += write(fd, base, 2);
	if (flags->ze && !flags->dt && !flags->da && flags->wi)
		count += ftdpf_width(fd, flags->wi - len, '0');
	if (flags->dt)
		count += ftdpf_width(fd, flags->pr - len, '0');
	if (!(flags->dt && !flags->pr && !n))
		ftdpf_print_base(fd, n, base + 2);
	if (flags->da && flags->wi)
		count += ftdpf_width(fd,
				flags->wi - ftdpf_max(flags->pr, len) - 2,
				' ');
	return (count + len);
}
