/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:51:11 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/05 13:36:13 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "ft_ssl.h"
#include "ft_printf.h"
#include "ft_getopt.h"
#include "dlst.h"
#include "memory.h"

static void	add_file(t_dlist **head, char *name, char *digest)
{
	t_input	input;
	int		fd;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		ft_fprintf(2, "%s: %s: No such file or directory\n", digest, name);
		return;
	}
	input.type = _FILE;
	input.str = name;
	input.fd = fd;
	ft_dlstappend(head, ft_dlstnew(&input, sizeof(input)));
}

static void	add_stdin(t_dlist **head, char *digest)
{
	t_input	input;

	if (read(0, NULL, 0) < 0)
	{
		ft_fprintf(2, "%s: cannot read stdin\n", digest);
	}
	input.type = STDIN;
	input.str = NULL;
	input.fd = 0;
	ft_dlstappend(head, ft_dlstnew(&input, sizeof(input)));
}

static void	add_string(t_dlist **head, char *s)
{
	t_input input;

	input.type = STRING;
	input.str = s;
	input.fd = -1;
	ft_dlstappend(head, ft_dlstnew(&input, sizeof(input)));
}

t_dlist		*parse_cmd(t_flags *flags, int ac, char *av[])
{
	t_dlist	*lst = NULL;
	int		ch;

	ft_bzero(flags, sizeof(t_flags));
	while ((ch = ft_getopt(ac, av, "pqs:r")) != -1)
	{
		if (ch == 'p')
		{
			flags->p = 1;
			add_stdin(&lst, av[0]);
		}
		else if (ch == 'r')
			flags->r = 1;
		else if (ch == 'q')
			flags->q = 1;
		else if (ch == 's')
			add_string(&lst, g_optarg);
		else
			return (NULL);
	}
	while (g_optind < ac)
		add_file(&lst, av[g_optind++], av[0]);
	if (lst == NULL)
		add_stdin(&lst, av[0]);
	return (lst);
}
