/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:59 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/03 18:57:53 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "dlst.h"

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

int				md5(char *input);
int				sha256(char *input);
t_dlist			*parse_cmd(t_flags *flags, int ac, char *argv[]);
int				process_input(t_dlist *lst, t_flags flags, int (*f)(char *));

#endif
