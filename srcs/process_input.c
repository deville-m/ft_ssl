/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:47:56 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/04 02:21:26 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_printf.h"
#include "memory.h"
#include "dlst.h"

static int	padding(t_hash *hash, ssize_t ret, char *buf, size_t len)
{
	char	*data;
	size_t	i;

	data = malloc(hash->chunk_len * 2);
	ft_memcpy(data, buf, ret);
	data[ret++] = 0x80;
	//TODO hard coded 4
	while (ret % hash->chunk_len != hash->chunk_len - 4)
		data[ret++] = 0x00;
	ft_memcpy(data + ret, &len, 4);
	i = 0;
	while (i < 512 / 8)
		ft_printf("%2.2hhx", data[i++]);
	write(1, "\n", 1);
	hash->hash_f(hash, data);
	if (ret > hash->chunk_len)
		hash->hash_f(hash, data + hash->chunk_len);
	free(data);
	return (1);
}

static int	basic_case(t_flags *flags, t_hash *hash)
{
	char	buf[64];
	ssize_t	ret;
	size_t	i;

	//TODO hard coded buf
	i = 0;
	hash->init_f(hash);
	while ((ret = read(0, buf, hash->chunk_len)) == hash->chunk_len)
	{
		hash->hash_f(hash, buf);
		i += ret;
	}
	i += ret;
	padding(hash, ret, buf, i);
	i = 0;
	while (i < hash->md_len)
		ft_printf("%2.2hhx", hash->out[i++]);
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
		t_flags *flags,
		t_hash *hash)
{
	if (!flags->p &&
		ft_dlstlen(input_list) == 1 &&
		((t_input *)input_list->content)->type == STDIN)
		return (basic_case(flags, hash));

	//ft_dlstiter(input_list, print_content);
	return (0);
}
