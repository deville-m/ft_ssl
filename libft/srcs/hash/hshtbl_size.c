/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hshtbl_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:52:32 by mdeville          #+#    #+#             */
/*   Updated: 2018/04/09 18:33:23 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

size_t		hshtbl_size(t_hshtbl *tbl)
{
	if (!tbl)
		return (0);
	return (tbl->tblsize);
}