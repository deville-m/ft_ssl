/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:51:11 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/12 18:03:38 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "ft_hash.h"
#include "ft_printf.h"
#include "ft_getopt.h"
#include "dlst.h"
#include "memory.h"

static void		add_file(t_dlist **head, char *name)
{
	t_input	input;

	input.type = _FILE;
	input.str = name;
	ft_dlstappend(head, ft_dlstnew(&input, sizeof(input)));
}

static t_dlist	*add_stdin(t_dlist **head, char *digest)
{
	t_input	input;

	if (read(0, NULL, 0) < 0)
	{
		ft_fprintf(2, "%s: cannot read stdin\n", digest);
		return (*head);
	}
	input.type = STDIN;
	input.str = NULL;
	input.fd = 0;
	ft_dlstappend(head, ft_dlstnew(&input, sizeof(input)));
	return (*head);
}

static void		add_string(t_dlist **head, char *s)
{
	t_input input;

	input.type = STRING;
	input.str = s;
	input.fd = -1;
	ft_dlstappend(head, ft_dlstnew(&input, sizeof(input)));
}

static t_dlist	*cleanup(t_dlist *lst)
{
	t_dlist	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		free(lst->content);
		lst = lst->next;
		free(tmp);
	}
	return (NULL);
}

t_dlist			*parse_cmd(t_flags *flags, int ac, char *av[])
{
	t_dlist	*lst;
	int		ch;

	lst = NULL;
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
			return (cleanup(lst));
	}
	while (g_optind < ac)
		add_file(&lst, av[g_optind++]);
	lst = (lst == NULL) ? add_stdin(&lst, av[0]) : lst;
	return (lst);
}
