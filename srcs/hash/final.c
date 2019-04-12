/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:30:58 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 18:03:28 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"
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

int		final_sha512(t_hash *hash)
{
	ssize_t i;

	i = 0;
	while (i < 8)
	{
		hash->lstate[i] = byte_swap_64(hash->lstate[i]);
		i++;
	}
	i = 0;
	while (i < hash->md_len)
		ft_printf("%2.2hhx", hash->out[i++]);
	return (1);
}
