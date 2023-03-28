/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/28 19:43:15 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_after_operator(char *s, char ***tab, int *check)
{
	*check = 1;
	if ((*(s + 1) == '\'') || (*(s + 1) == '\"'))
		s = copy_quoted(s, tab, check);
	return (s);
}

char	**split_token(t_prg *prg)
{
	char	**tab;
	int		count;
	int		check;
	char	*s;

	s = prg->input;
	if (!s)
		return (NULL);
	check = 1;
	count = count_tab(s);
	tab = malloc(sizeof(char *) * (count + 1));
	s = check_first_quote(s, &tab, &check);
	while (*s)
	{
		if (has_operators(*s, ">|<"))
			s = copy_operator(s, &tab, &check);
		if (check && !(has_operators(*s, ">|< ")))
			s = copy_token(s, &tab, &check);
		else if (!check && (has_operators(*s, ">|< ")))
			s = check_after_operator(s, &tab, &check);
		s++;
	}
	*tab = 0;
	return (tab - count);
}
