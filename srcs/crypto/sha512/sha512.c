/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:26 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 18:04:32 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"
#include "memory.h"

static const uint64_t g_k[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

int			init_sha512(t_hash *hash)
{
	hash->lstate[0] = 0x6a09e667f3bcc908;
	hash->lstate[1] = 0xbb67ae8584caa73b;
	hash->lstate[2] = 0x3c6ef372fe94f82b;
	hash->lstate[3] = 0xa54ff53a5f1d36f1;
	hash->lstate[4] = 0x510e527fade682d1;
	hash->lstate[5] = 0x9b05688c2b3e6c1f;
	hash->lstate[6] = 0x1f83d9abfb41bd6b;
	hash->lstate[7] = 0x5be0cd19137e2179;
	hash->md_len = 64;
	hash->chunk_len = 128;
	hash->hash_f = sha512;
	hash->pad_f = pad_sha512;
	hash->final_f = final_sha512;
	hash->out = (char *)hash->lstate;
	return (1);
}

static void	rounds(uint64_t *tmp, uint64_t *w)
{
	uint64_t	temp[2];
	size_t		i;

	i = 0;
	while (i < 80)
	{
		temp[0] = tmp[7] + eps_1_512(tmp[4]);
		temp[0] += ch_512(tmp[4], tmp[5], tmp[6]) + g_k[i] + w[i];
		temp[1] = eps_0_512(tmp[0]) + maj_512(tmp[0], tmp[1], tmp[2]);
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
}

static void	init_w(uint64_t *w, uint64_t *m)
{
	size_t i;

	i = 0;
	while (i < 80)
	{
		if (i < 16)
			w[i] = byte_swap_64(m[i]);
		else
		{
			w[i] = sigma_1_512(w[i - 2]) + w[i - 7];
			w[i] += sigma_0_512(w[i - 15]) + w[i - 16];
		}
		i++;
	}
}

int			sha512(t_hash *hash, const char *chunk)
{
	uint64_t	tmp[8];
	uint64_t	w[80];
	uint64_t	*m;
	uint64_t	i;

	ft_memcpy(tmp, hash->lstate, 8 * sizeof(uint64_t));
	m = (uint64_t *)chunk;
	init_w(w, m);
	rounds(tmp, w);
	i = 0;
	while (i < 8)
	{
		hash->lstate[i] += tmp[i];
		i++;
	}
	return (1);
}
