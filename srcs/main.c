/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:16:30 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 18:01:55 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_string.h"
#include "ft_printf.h"

t_cmd	g_cmd_list[NB_CMD] = {
	{"md5", CMD_HASH, hash_main},
	{"sha256", CMD_HASH, hash_main},
	{"sha512", CMD_HASH, hash_main},
	{"sha224", CMD_HASH, hash_main},
	{"sha384", CMD_HASH, hash_main},
};

t_cmd	*check_cmd(char *av)
{
	size_t i;

	i = 0;
	while (i < NB_CMD)
	{
		if (ft_strequ(g_cmd_list[i].name, av))
		{
			return (&(g_cmd_list[i]));
		}
		i++;
	}
	return (NULL);
}

int		usage(char *prog)
{
	ft_fprintf(2, "usage: %s cmd [-pqr] [-s string]\n", prog);
	ft_fprintf(2, "\nMessage Digest commands\nmd5\tsha256\tsha512");
	ft_fprintf(2, "\tsha224\tsha384\n");
	return (1);
}

int		main(int ac, char *av[])
{
	t_cmd	*cmd;

	cmd = NULL;
	if (ac == 1)
		return (usage(av[0]));
	if ((cmd = check_cmd(av[1])) == NULL)
		return (usage(av[0]));
	return (cmd->prog(ac, av));
}
