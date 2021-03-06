/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:57:25 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 18:03:24 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_hash.h"
#include "memory.h"

uint64_t	byte_swap_64(uint64_t x)
{
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8 | (x & 0xFF00FF00FF00FF00) >> 8;
	return (x);
}

uint32_t	byte_swap_32(uint32_t x)
{
	return (((x >> 24) & 0xff)
			| ((x << 8) & 0xff0000)
			| ((x >> 8) & 0xff00)
			| ((x << 24) & 0xff000000));
}

int			pad_md5(t_hash *hash, ssize_t ret, char *buf, uint64_t len)
{
	char	data[128];

	ft_memcpy(data, buf, ret);
	data[ret++] = 0x80;
	while (ret % hash->chunk_len != hash->chunk_len - 8)
		data[ret++] = 0x00;
	ft_memcpy(data + ret, &len, sizeof(len));
	hash->hash_f(hash, data);
	if (ret > hash->chunk_len)
		hash->hash_f(hash, data + hash->chunk_len);
	return (1);
}

int			pad_sha256(t_hash *hash, ssize_t ret, char *buf, uint64_t len)
{
	char		data[128];

	ft_memcpy(data, buf, ret);
	data[ret++] = 0x80;
	while (ret % hash->chunk_len != hash->chunk_len - 8)
		data[ret++] = 0x00;
	len = byte_swap_64(len);
	ft_memcpy(data + ret, &len, sizeof(len));
	hash->hash_f(hash, data);
	if (ret > hash->chunk_len)
		hash->hash_f(hash, data + hash->chunk_len);
	return (1);
}

int			pad_sha512(t_hash *hash, ssize_t ret, char *buf, uint64_t len)
{
	char		data[256];

	ft_memcpy(data, buf, ret);
	data[ret++] = 0x80;
	while (ret % hash->chunk_len != hash->chunk_len - 16)
		data[ret++] = 0x00;
	ft_memset(data + ret, 0, 8);
	ret += 8;
	len = byte_swap_64(len);
	ft_memcpy(data + ret, &len, sizeof(len));
	hash->hash_f(hash, data);
	if (ret > hash->chunk_len)
		hash->hash_f(hash, data + hash->chunk_len);
	return (1);
}
