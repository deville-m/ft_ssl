/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:26 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/04 00:24:28 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		init_sha256(t_hash *hash)
{
	hash->state[0] = 0x67452301;
	hash->state[1] = 0xEFCDAB89;
	hash->state[2] = 0x98BADCFE;
	hash->state[3] = 0x10325476;
	hash->md_len = 32;
	hash->chunk_len = 64;
	hash->hash_f = sha256;
	hash->out = (char *)hash->state;
	return (1);
}

int		sha256(t_hash *hash, const char *buf)
{
	return (1);
}
