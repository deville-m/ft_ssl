/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:47:56 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/03 19:11:51 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_printf.h"
#include "dlst.h"

static int basic_case(t_dlist *input_list, t_flags flags, int (*hash_f)(char *))
{
	return (0);
}

void print_content(t_dlist *elem)
{
	t_input *input;

	input = (t_input *)elem->content;
	if (input->type == STRING)
		ft_printf("type: STRING - value: %s\n", input->str);
	else if (input->type == _FILE)
		ft_printf("type: FILE - name: %s\n", input->str);
	else
		ft_printf("type: STDIN\n");
}

int process_input(t_dlist *input_list, t_flags flags, int (*hash_f)(char *))
{
	if (!flags.p &&
		ft_dlstlen(input_list) == 1 &&
		((t_input *)input_list->content)->type == STDIN)
		return (basic_case(input_list, flags, hash_f));

	ft_dlstiter(input_list, print_content);
	return (0);
}
