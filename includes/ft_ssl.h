/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:33:59 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 17:54:08 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdint.h>

# define NB_CMD 5

enum			e_cmd_type
{
	CMD_HASH,
	CMD_CIPHER,
	CMD_OTHER
};

typedef struct	s_cmd
{
	char			*name;
	enum e_cmd_type	type;
	int				(*prog)(int ac, char *av[]);
}				t_cmd;

int				hash_main(int ac, char *av[]);

#endif
