/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:52:35 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/08 17:01:24 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	rotate_right_64(uint64_t n, uint64_t d)
{
	return ((n >> d) | (n << (64 - d)));
}

uint64_t	ch_512(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (~x & z));
}

uint64_t	maj_512(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint64_t	eps_0_512(uint64_t x)
{
	return (rotate_right_64(x, 28)
			^ rotate_right_64(x, 34)
			^ rotate_right_64(x, 39));
}

uint64_t	eps_1_512(uint64_t x)
{
	return (rotate_right_64(x, 14)
			^ rotate_right_64(x, 18)
			^ rotate_right_64(x, 41));
}
