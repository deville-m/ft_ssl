/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:59 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/03 20:56:10 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include "dlst.h"
# define CHUNK_SIZE 512 / 8
# define MD5_DIGEST_LENGTH 128 / 8
# define SHA256_DIGEST_LENGTH 256 / 8

typedef struct	s_state
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;
	uint32_t g;
	uint32_t h;
}				t_state;

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

t_state			md5(t_state state, const char *buf);
t_state			sha256(t_state state, const char *buf);
t_dlist			*parse_cmd(t_flags *flags, int ac, char *argv[]);
int				process_input(
							t_dlist *lst,
							t_flags flags,
							t_state (*hash_f)(t_state, const char *));

#endif
