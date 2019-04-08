/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:30:58 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/08 14:40:23 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_printf.h"

int		final_md5(t_hash *hash)
{
	ssize_t i;

	i = 0;
	while (i < hash->md_len)
		ft_printf("%2.2hhx", hash->out[i++]);
	return (1);
}

int		final_sha256(t_hash *hash)
{
	ssize_t i;

	i = 0;
	while (i < 8)
	{
		hash->state[i] = byte_swap_32(hash->state[i]);
		i++;
	}
	i = 0;
	while (i < hash->md_len)
		ft_printf("%2.2hhx", hash->out[i++]);
	return (1);
}
