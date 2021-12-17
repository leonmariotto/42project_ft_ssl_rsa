/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_random.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:22:15 by leon              #+#    #+#             */
/*   Updated: 2021/12/15 11:10:19 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int			open_randomfd(char *file)
{
	int fd;

	if (file == NULL)
		fd = open("/dev/urandom", O_RDONLY);
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
		err_return("open_randomfd: open error");
	return (fd);

}

int			get_random(void	*ptr, size_t size, int randomfd)
{
	if (randomfd <= 0)
		err_return("get_random: Invalid file descriptor");
	if (read(randomfd, ptr, size) < 0)
		err_return("get_random: read error");
	return (1);
}
