/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:13:17 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/10 01:35:13 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	compare_names(void *content1, void *content2)
{
	return (ft_strncmp(((t_file *)content1)->name,
			((t_file *)content2)->name,
			ft_strlen(((t_file *)content1)->name)));
}

int	is_strs_equal(char *str1, char *str2)
{
	return (!ft_strncmp(str1, str2, ft_strlen(str1))
		&& (ft_strlen(str1) == ft_strlen(str2)));
}
