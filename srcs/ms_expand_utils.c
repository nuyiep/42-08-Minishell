/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:29:40 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/11 17:53:11 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int *get_new_token_size(
{
	int size_old;
	int size_var;
	int size_expansion;
	int new_size;
	
	size_old = ft_strlen(old);
	size_var = ft_strlen(var);
	size_expansion = ft_strlen(expansion);
	
	
}

char *create_new_token(char **pair, )