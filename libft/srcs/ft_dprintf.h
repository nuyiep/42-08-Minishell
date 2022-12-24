/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:00:22 by maliew            #+#    #+#             */
/*   Updated: 2022/09/29 01:40:45 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

/*
	da	dash;
	ze	zero;
	dt	dot;
	ha	hash;
	sp	space;
	pl	plus;
	wi	width;
	pr	precision;
	sr	specifier;
*/
typedef struct s_ftdpf_flags
{
	int		da;
	int		ze;
	int		dt;
	int		ha;
	int		sp;
	int		pl;
	int		wi;
	int		pr;
	char	sr;
}	t_ftdpf_flags;

t_ftdpf_flags	*ftdpf_get_flags(char *string, int *i);

int				ftdpf_char(int fd, char c, t_ftdpf_flags *flags);
int				ftdpf_str(int fd, char *s, t_ftdpf_flags *flags);
int				ftdpf_int(int fd, long n, t_ftdpf_flags *flags);
int				ftdpf_hex(int fd, unsigned long n, t_ftdpf_flags *flags,
					char *base);
int				ftdpf_ptr(int fd, unsigned long n, t_ftdpf_flags *flags,
					char *base);

int				ftdpf_width(int fd, int width, char c);
void			ftdpf_get_neg(long *n, int *neg);
int				ftdpf_max(int a, int b);
int				ftdpf_get_len_base(unsigned long n, int base_len);
void			ftdpf_print_base(int fd, unsigned long n, char *base);

int				ftdpf_print_args(int fd, va_list args, t_ftdpf_flags *flags);
int				ft_dprintf(int fd, const char *format, ...);

#endif