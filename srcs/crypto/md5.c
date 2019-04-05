/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:30:58 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/05 16:37:20 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "memory.h"

static const uint32_t g_r[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

int			init_md5(t_hash *hash)
{
	hash->state[0] = 0x67452301;
	hash->state[1] = 0xEFCDAB89;
	hash->state[2] = 0x98BADCFE;
	hash->state[3] = 0x10325476;
	hash->md_len = 16;
	hash->chunk_len = 64;
	hash->hash_f = md5;
	hash->pad_f = pad_512;
	hash->out = (char *)hash->state;
	return (1);
}

static int	left_rotate(uint32_t n, uint32_t d)
{
	return ((n << d) | (n >> (32 - d)));
}

static void	apply(uint32_t f, uint32_t *tmp, uint32_t i)
{
	tmp[0] = tmp[3];
	tmp[3] = tmp[2];
	tmp[2] = tmp[1];
	tmp[1] += left_rotate(f, g_r[i]);
}

static void	round(uint32_t *tmp, uint32_t *w, uint32_t i)
{
	uint32_t f;
	uint32_t g;

	if (i <= 15)
	{
		f = (tmp[1] & tmp[2]) | (~tmp[1] & tmp[3]);
		g = i;
	}
	else if (i <= 31)
	{
		f = (tmp[3] & tmp[1]) | (~tmp[3] & tmp[2]);
		g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		f = tmp[1] ^ tmp[2] ^ tmp[3];
		g = (3 * i + 5) % 16;
	}
	else
	{
		f = tmp[2] ^ (tmp[1] | ~tmp[3]);
		g = (7 * i) % 16;
	}
	f = f + tmp[0] + g_k[i] + w[g];
	apply(f, tmp, i);
}

int			md5(t_hash *hash, const char *chunk)
{
	uint32_t *w;
	uint32_t tmp[4];
	uint32_t i;

	ft_memcpy(tmp, hash->state, 4 * sizeof(uint32_t));
	w = (uint32_t *)chunk;
	i = 0;
	while (i < 64)
	{
		round(tmp, w, i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		hash->state[i] += tmp[i];
		i++;
	}
	return (1);
}
