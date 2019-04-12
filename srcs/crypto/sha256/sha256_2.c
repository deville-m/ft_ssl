/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:52:35 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 18:04:12 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"

uint32_t	rotate_right_32(uint32_t n, uint32_t d)
{
	return ((n >> d) | (n << (32 - d)));
}

uint32_t	ch_256(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint32_t	maj_256(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	eps_0_256(uint32_t x)
{
	return (rotate_right_32(x, 2)
			^ rotate_right_32(x, 13)
			^ rotate_right_32(x, 22));
}

uint32_t	eps_1_256(uint32_t x)
{
	return (rotate_right_32(x, 6)
			^ rotate_right_32(x, 11)
			^ rotate_right_32(x, 25));
}
