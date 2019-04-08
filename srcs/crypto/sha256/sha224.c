/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:10:12 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/08 15:17:16 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			init_sha224(t_hash *hash)
{
	hash->state[0] = 0xc1059ed8;
	hash->state[1] = 0x367cd507;
	hash->state[2] = 0x3070dd17;
	hash->state[3] = 0xf70e5939;
	hash->state[4] = 0xffc00b31;
	hash->state[5] = 0x68581511;
	hash->state[6] = 0x64f98fa7;
	hash->state[7] = 0xbefa4fa4;
	hash->md_len = 28;
	hash->chunk_len = 64;
	hash->hash_f = sha256;
	hash->pad_f = pad_sha;
	hash->final_f = final_sha256;
	hash->out = (char *)hash->state;
	return (1);
}
