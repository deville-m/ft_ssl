/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:47:56 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/08 16:48:03 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "memory.h"
#include "dlst.h"

int		digest_string(t_input *input, t_flags *flags, t_hash *hash)
{
	ssize_t		i;
	uint64_t	len;

	if (!flags->q && !flags->r)
		ft_printf("%s (\"%s\") = ", hash->name, input->str);
	hash->init_f(hash);
	len = ft_strlen(input->str);
	i = len;
	while (i > hash->chunk_len)
	{
		hash->hash_f(hash, input->str + (len - i));
		i -= hash->chunk_len;
	}
	hash->pad_f(hash, i, input->str + (len - i), len * 8);
	hash->final_f(hash);
	if (!flags->q && flags->r)
		ft_printf(" \"%s\"", input->str);
	return (1);
}

int		digest_fd(int fd, t_input *input, t_flags *flags, t_hash *hash)
{
	char		buf[4096];
	ssize_t		ret;
	ssize_t		i;

	i = 0;
	hash->init_f(hash);
	while ((ret = read(fd, buf, hash->chunk_len)) == hash->chunk_len)
	{
		if (flags->p && input->type == STDIN)
			write(1, buf, ret);
		hash->hash_f(hash, buf);
		i += ret;
	}
	if (flags->p && input->type == STDIN)
		write(1, buf, ret);
	i += ret;
	hash->pad_f(hash, ret, buf, i * 8);
	hash->final_f(hash);
	return (1);
}

void	process_file(t_input *input, t_flags *flags, t_hash *hash)
{
	int fd;

	if ((fd = open(input->str, O_RDONLY)) < 0)
	{
		ft_fprintf(
				2,
				"%s: %s: No such file or directory",
				hash->name,
				input->str);
		return ;
	}
	if (!flags->q && !flags->r)
		ft_printf("%s (%s) = ", hash->name, input->str);
	digest_fd(fd, input, flags, hash);
	if (!flags->q && flags->r)
		ft_printf(" %s", input->str);
	close(fd);
}

int		process_input(t_input *input, t_flags *flags, t_hash *hash)
{
	if (input->type == STDIN)
		digest_fd(0, input, flags, hash);
	else if (input->type == STRING)
		digest_string(input, flags, hash);
	else
		process_file(input, flags, hash);
	write(1, "\n", 1);
	free(input);
	return (1);
}

int		process_input_list(
					t_dlist *input_list,
					t_flags *flags,
					t_hash *hash)
{
	t_dlist *to_free;
	t_input *tmp;

	if (!flags->p &&
		ft_dlstlen(input_list) == 1 &&
		((t_input *)input_list->content)->type == STDIN)
	{
		digest_fd(0, (t_input *)input_list->content, flags, hash);
		write(1, "\n", 1);
		free((t_input *)input_list->content);
		free(input_list);
		return (0);
	}
	while (input_list != NULL)
	{
		to_free = input_list;
		tmp = (t_input *)input_list->content;
		process_input(tmp, flags, hash);
		input_list = input_list->next;
		free(to_free);
	}
	return (0);
}
