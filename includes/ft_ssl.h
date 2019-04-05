/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:59 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/05 16:51:05 by mdeville         ###   ########.fr       */
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

int             pad_512(t_hash *hash, ssize_t ret, char *buf, uint64_t len);
int             pad_1024(t_hash *hash, ssize_t ret, char *buf, uint64_t len);

t_dlist			*parse_cmd(t_flags *flags, int ac, char *argv[]);
int				process_input_list(
							t_dlist *lst,
							t_flags *flags,
							t_hash *hash);

#endif
