/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:26 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/05 17:12:58 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "memory.h"

static const uint32_t g_k[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

int		init_sha256(t_hash *hash)
{
	hash->state[0] = 0x6a09e667;
	hash->state[1] = 0xbb67ae85;
	hash->state[2] = 0x3c6ef372;
	hash->state[3] = 0xa54ff53a;
	hash->state[4] = 0x510e527f;
	hash->state[5] = 0x9b05688c;
	hash->state[6] = 0x1f83d9ab;
	hash->state[7] = 0x5be0cd19;
	hash->md_len = 32;
	hash->chunk_len = 64;
	hash->hash_f = sha256;
	hash->pad_f = pad_1024;
	hash->out = (char *)hash->state;
	return (1);
}

uint32_t	rotate_right(uint32_t n, uint32_t d)
{
	return ((n >> d) | (n << (32 - d)));
}

uint32_t	ch_256(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint32_t	maj_256(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y ^ z));
}

uint32_t	sigma_0_256(uint32_t x)
{
	return (rotate_right(x, 2) ^ rotate_right(x, 13) ^ rotate_right(x, 22));
}

uint32_t	sigma_1_256(uint32_t x)
{
	return (rotate_right(x, 6) ^ rotate_right(x, 11) ^ rotate_right(x, 25));
}

uint32_t	delta_0_256(uint32_t x)
{
	return (rotate_right(x, 7) ^ rotate_right(x, 18) ^ (x >> 3));
}

uint32_t	delta_1_256(uint32_t x)
{
	return (rotate_right(x, 17) ^ rotate_right(x, 19) ^ (x >> 10));
}

int		sha256(t_hash *hash, const char *chunk)
{
	uint32_t	tmp[8];
	uint32_t	w[64];
	uint32_t	*m;
	uint32_t	i;
	uint32_t	temp[2];

	ft_memcpy(tmp, hash->state, 8 * sizeof(uint32_t));
	m = (uint32_t *)chunk;
	i = 0;
	while (i < 64)
	{
		if (i <= 15)
			w[i] = m[i];
		else
			w[i] = delta_1_256(w[i - 2]) + w[i - 7] + delta_0_256(w[i - 15]) + w[i - 16];
		i++;
	}
	i = 0;
	while (i < 64)
	{
		temp[0] = tmp[7] + sigma_1_256(tmp[4]) + ch_256(tmp[4], tmp[5], tmp[6]) + g_k[i] + w[i];
		temp[1] = sigma_0_256(tmp[0]) + maj_256(tmp[0], tmp[1], tmp[2]);
		tmp[7] = tmp[6];
		tmp[6] = tmp[5];
		tmp[5] = tmp[4];
		tmp[4] = tmp[3] + temp[0];
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] = tmp[0];
		tmp[0] = temp[0] + temp[1];
		i++;
	}
	i = 0;
	while (i < 8)
	{
		hash->state[i] += tmp[i];
		i++;
	}
	return (1);
}
