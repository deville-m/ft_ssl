/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:59 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/08 17:42:33 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include "dlst.h"

typedef struct	s_hash
{
	char		*name;
	uint32_t	state[8];
	uint64_t	lstate[8];
	ssize_t		md_len;
	ssize_t		chunk_len;
	char		*out;
	int			(*hash_f)(struct s_hash *, const char *);
	int			(*init_f)(struct s_hash *);
	int			(*pad_f)(struct s_hash *hash, ssize_t, char *, uint64_t);
	int			(*final_f)(struct s_hash *hash);
}				t_hash;

typedef struct	s_flags
{
	int			p;
	int			q;
	int			r;
}				t_flags;

typedef enum	e_type
{
	STRING,
	STDIN,
	_FILE
}				t_type;

typedef struct	s_input
{
	t_type		type;
	char		*str;
	int			fd;
}				t_input;

int				init_md5(t_hash *hash);
int				md5(t_hash *hash, const char *buf);

int				init_sha256(t_hash *hash);
int				sha256(t_hash *hash, const char *buf);

int				init_sha224(t_hash *hash);

uint32_t		rotate_right_32(uint32_t n, uint32_t d);
uint32_t		eps_1_256(uint32_t x);
uint32_t		eps_0_256(uint32_t x);
uint32_t		sigma_0_256(uint32_t x);
uint32_t		sigma_1_256(uint32_t x);
uint32_t		maj_256(uint32_t x, uint32_t y, uint32_t z);
uint32_t		ch_256(uint32_t x, uint32_t y, uint32_t z);

int				init_sha512(t_hash *hash);
int				sha512(t_hash *hash, const char *buf);

int				init_sha384(t_hash *hash);

uint64_t		rotate_right_64(uint64_t n, uint64_t d);
uint64_t		eps_1_512(uint64_t x);
uint64_t		eps_0_512(uint64_t x);
uint64_t		sigma_0_512(uint64_t x);
uint64_t		sigma_1_512(uint64_t x);
uint64_t		maj_512(uint64_t x, uint64_t y, uint64_t z);
uint64_t		ch_512(uint64_t x, uint64_t y, uint64_t z);

uint32_t		byte_swap_32(uint32_t x);
uint64_t		byte_swap_64(uint64_t x);

int				pad_md5(t_hash *hash, ssize_t ret, char *buf, uint64_t len);
int				pad_sha(t_hash *hash, ssize_t ret, char *buf, uint64_t len);

int				final_md5(t_hash *hash);
int				final_sha256(t_hash *hash);
int				final_sha512(t_hash *hash);

t_dlist			*parse_cmd(t_flags *flags, int ac, char *argv[]);
int				process_input_list(
							t_dlist *lst,
							t_flags *flags,
							t_hash *hash);

#endif
