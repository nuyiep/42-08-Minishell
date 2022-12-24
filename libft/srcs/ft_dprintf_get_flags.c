/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_get_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:39:51 by maliew            #+#    #+#             */
/*   Updated: 2022/09/29 01:40:48 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	init_flags(t_ftdpf_flags *flags)
{
	flags->da = 0;
	flags->dt = 0;
	flags->ha = 0;
	flags->pl = 0;
	flags->pr = 0;
	flags->sp = 0;
	flags->sr = 0;
	flags->wi = 0;
	flags->ze = 0;
}

static void	parse_flags(t_ftdpf_flags *flags, char *string, int *i)
{
	while (ft_strchr("#0- +", string[*i]))
	{
		if (string[*i] == '#')
			flags->ha = 1;
		else if (string[*i] == '0')
			flags->ze = 1;
		else if (string[*i] == '-')
			flags->da = 1;
		else if (string[*i] == ' ')
			flags->sp = 1;
		else if (string[*i] == '+')
			flags->pl = 1;
		(*i)++;
	}
}

static void	parse_wp(t_ftdpf_flags *flags, char *string, int *i)
{
	while (ft_isdigit(string[*i]))
	{
		flags->wi = flags->wi * 10 + string[*i] - '0';
		(*i)++;
	}
	if (string[*i] == '.' && string[(*i) + 1])
	{
		(*i)++;
		flags->dt = 1;
		while (ft_isdigit(string[*i]))
		{
			flags->pr = flags->pr * 10 + string[*i] - '0';
			(*i)++;
		}
	}
}

t_ftdpf_flags	*ftdpf_get_flags(char *string, int *i)
{
	t_ftdpf_flags	*flags;

	flags = (t_ftdpf_flags *)malloc(sizeof(t_ftdpf_flags));
	if (!flags)
		return (0);
	init_flags(flags);
	(*i)++;
	parse_flags(flags, string, i);
	parse_wp(flags, string, i);
	flags->sr = string[*i];
	return (flags);
}
