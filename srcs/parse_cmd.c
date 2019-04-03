/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:51:11 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/03 16:07:31 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ssl.h"
#include "ft_getopt.h"
#include "dlst.h"
#include "memory.h"

void add_string(t_dlist **head, char *s)
{
       
}

t_dlist *parse_cmd(t_flags *flags, int ac, char *av[])
{
    t_dlist *lst;
    char    ch;

    ft_bzero(flags, sizeof(t_flags));
    while ((ch = ft_getopt(ac, av, "pqs:r")) != -1) {
        if (ch == 'p')
            flags->p = 1;
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
        add_file(&lst, av[g_optind++])
    if (lst == NULL || flags->p)
        add_stdin(&lst)
    return (lst);
}
