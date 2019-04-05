/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:57:25 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/05 16:48:05 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl.h"
#include "memory.h"

int				pad_512(t_hash *hash, ssize_t ret, char *buf, uint64_t len)
{
	char	data[1024];

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

static uint64_t byte_swap(uint64_t x)
{
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
	return x;
}

int				pad_1024(t_hash *hash, ssize_t ret, char *buf, uint64_t len)
{
	char		data[2048];

	ft_memcpy(data, buf, ret);
	data[ret++] = 0x80;
	while (ret % hash->chunk_len != hash->chunk_len - 8)
		data[ret++] = 0x00;
	len = byte_swap(len);
	ft_memcpy(data + ret, &len, sizeof(len));
	hash->hash_f(hash, data);
	if (ret > hash->chunk_len)
		hash->hash_f(hash, data + hash->chunk_len);
	return (1);
}
