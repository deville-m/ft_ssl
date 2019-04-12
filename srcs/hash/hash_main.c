/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:51:02 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 18:02:57 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_printf.h"
#include "ft_string.h"
#include "ft_hash.h"
#include "dlst.h"

t_cmd_hash	g_cmd_hash_list[NB_CMD_HASH] = {
	{"md5", "MD5", init_md5},
	{"sha256", "SHA256", init_sha256},
	{"sha512", "SHA512", init_sha512},
	{"sha224", "SHA224", init_sha224},
	{"sha384", "SHA384", init_sha384},
};

void	set_init(t_hash *hash, char *name)
{
	size_t i;

	i = 0;
	while (i < NB_CMD_HASH)
	{
		if (ft_strequ(g_cmd_hash_list[i].name, name))
			break ;
		i++;
	}
	hash->name = g_cmd_hash_list[i].out;
	hash->init_f = g_cmd_hash_list[i].init_f;
}

int		hash_main(int ac, char *av[])
{
	t_flags		flags;
	t_hash		hash;
	t_dlist		*input_list;

	set_init(&hash, av[1]);
	input_list = parse_cmd(&flags, ac - 1, av + 1);
	if (input_list == NULL)
		return (1);
	return (process_input_list(input_list, &flags, &hash));
}
