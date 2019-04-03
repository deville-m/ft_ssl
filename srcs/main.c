/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:51:02 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/03 14:16:56 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "ft_ssl.h"
#include "dlst.h"

int main(int ac, char *av[])
{
    t_flags     flags;
    int         (*hash_f)(char *);
    t_dlist      *input_list;

    if (ac == 1)
    {
        ft_fprintf(2, "usage: %s md5|sha256 [-sp [-q | -r]]\n", av[0]);
        return (1); 
    }
    if (ft_strequ(av[1], "md5"))
        hash_f = md5;
    else if (ft_strequ(av[1], "sha256"))
        hash_f = sha256;
    else
    {
        ft_fprintf(2, "usage: %s md5|sha256 [-sp [-q | -r]]\n", av[0]); 
        return (1);
    }
    input_list = parse_cmd(&flags, ac - 1, av + 1);
    if (input_list == NULL)
        return (1);
    /*return (compute_hash(flags, input_list));*/
    return (0);
}
