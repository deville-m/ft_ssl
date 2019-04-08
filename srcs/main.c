/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:51:02 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/08 18:26:00 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_printf.h"
#include "ft_string.h"
#include "ft_ssl.h"
#include "dlst.h"

int	set_init(t_hash *hash, char *name)
{
	size_t i;

	if (ft_strequ(name, "md5"))
		hash->init_f = init_md5;
	else if (ft_strequ(name, "sha256"))
		hash->init_f = init_sha256;
	else if (ft_strequ(name, "sha224"))
		hash->init_f = init_sha224;
	else if (ft_strequ(name, "sha512"))
		hash->init_f = init_sha512;
	else if (ft_strequ(name, "sha384"))
		hash->init_f = init_sha384;
	else
		return (0);
	i = 0;
	while (name[i])
	{
		name[i] = ft_toupper(name[i]);
		i++;
	}
	hash->name = name;
	return (1);
}

int	usage(char *prog)
{
	ft_fprintf(2, "usage: %s cmd [-pqr] [-s string]\n", prog);
	ft_fprintf(2, "\nMessage Digest commands\nmd5\tsha256\tsha512");
	ft_fprintf(2, "\tsha224\tsha384\n");
	return (1);
}

int	main(int ac, char *av[])
{
	t_flags		flags;
	t_hash		hash;
	t_dlist		*input_list;

	if (ac == 1)
		return (usage(av[0]));
	if (set_init(&hash, av[1]) == 0)
		return (usage(av[0]));
	input_list = parse_cmd(&flags, ac - 1, av + 1);
	if (input_list == NULL)
		return (1);
	return (process_input_list(input_list, &flags, &hash));
}
