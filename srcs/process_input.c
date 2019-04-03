/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:47:56 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/03 21:05:03 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_printf.h"
#include "memory.h"
#include "dlst.h"

static t_state	init_md5(void)
{
	t_state state;

	state.a = 0x67452301;
	state.b = 0xEFCDAB89;
	state.c = 0x98BADCFE;
	state.d = 0x10325476;
	return (state);
}

static t_state	init_sha256(void)
{
	t_state state = {0};

	return (state);
}

static t_state	process_padding(
							t_state state,
							size_t ret,
							char *buf,
							t_state (*hash_f)(t_state, const char *))
{
	char	data[CHUNK_SIZE * 2];

	ft_memcpy(data, buf, ret);
	//padding here
	state = hash_f(state, data);
	if (ret > CHUNK_SIZE)
		state = hash_f(state, date + CHUNK_SIZE);
	return (state);
}

static int	basic_case(t_flags flags, t_state (*hash_f)(t_state, const char *))
{
	char 	buf[CHUNK_SIZE];
	ssize_t	ret;
	t_state	state;
	size_t	len;
	size_t	i;

	if (hash_f == md5)
	{
		len = MD5_DIGEST_LENGTH;
		state = init_md5();
	}
	else
	{
		len = SHA256_DIGEST_LENGTH;
		state = init_sha256();
	}
	while ((ret = read(0, buf, CHUNK_SIZE)) == CHUNK_SIZE)
		state = hash_f(state, buf);
	state = process_padding(state, buf);
	i = 0;
	while (i < len)
		ft_printf("%2.2hhx", ((char *)&state)[i++]);
	write(1, "\n", 1);
	return (0);
}

static void	print_content(t_dlist *elem)
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

int	process_input(
		t_dlist *input_list,
		t_flags flags,
		t_state (*hash_f)(t_state, const char *))
{
	if (!flags.p &&
		ft_dlstlen(input_list) == 1 &&
		((t_input *)input_list->content)->type == STDIN)
		return (basic_case(flags, hash_f));

	//ft_dlstiter(input_list, print_content);
	return (0);
}
