/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:26 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/08 18:25:07 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "memory.h"

int			init_sha384(t_hash *hash)
{
	hash->lstate[0] = 0xcbbb9d5dc1059ed8;
	hash->lstate[1] = 0x629a292a367cd507;
	hash->lstate[2] = 0x9159015a3070dd17;
	hash->lstate[3] = 0x152fecd8f70e5939;
	hash->lstate[4] = 0x67332667ffc00b31;
	hash->lstate[5] = 0x8eb44a8768581511;
	hash->lstate[6] = 0xdb0c2e0d64f98fa7;
	hash->lstate[7] = 0x47b5481dbefa4fa4;
	hash->md_len = 48;
	hash->chunk_len = 128;
	hash->hash_f = sha512;
	hash->pad_f = pad_sha;
	hash->final_f = final_sha512;
	hash->out = (char *)hash->lstate;
	return (1);
}
