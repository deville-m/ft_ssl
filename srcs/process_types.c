/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:42:13 by mdeville          #+#    #+#             */
/*   Updated: 2019/04/04 16:17:29 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_ssl.h"
#include "ft_printf.h"

void	digest_fd(int fd, t_file input, t_flags *flags, t_hash *hash)
{
	char		buf[4096];
	ssize_t		ret;
	uint64_t	i;

	i = 0;
	hash->init_f(hash);
	while ((ret = read(fd, buf, hash->chunk_len)) == hash->chunk_len)
	{
		if (flags->p && input->type == STDIN)
			write(1, buf, ret);
		hash->hash_f(hash, buf);
		i += ret;
	}
	i += ret;
	padding(hash, ret, buf, i * 8);
	i = 0;
	while (i < hash->md_len)
		ft_printf("%2.2hhx", hash->out[i++]);
	write(1, "\n", 1);
	return (0);
}

void	process_file(t_input *input, t_flags *flags, t_hash *hash)
{
	int fd;

	if ((fd = open(input->str, O_RDONLY)) < 0)
		ft_fprintf(
				2,
				"%s: %s: No such file or directory\n",
				hash->name,
				input->str);
	if (!flags->q && !flags->r)
			ft_printf("(%s) = ", hash->name);

	if (!flags->q && flags->r)
		ft_printf("%s\n", input->str);
}
