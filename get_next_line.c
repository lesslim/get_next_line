/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:30:30 by rberon-s          #+#    #+#             */
/*   Updated: 2018/12/07 18:30:31 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		makeline(char **line, char **mfd, int fd)
{
	char *s;

	if (ft_strchr(mfd[fd], 10))
	{
		*line = ft_strsub(mfd[fd], 0, ft_strchr(mfd[fd], 10) - mfd[fd]);
		s = ft_strdup(ft_strchr(mfd[fd], 10) + 1);
		free(mfd[fd]);
		mfd[fd] = s;
		if (mfd[fd][0] == '\0')
			ft_strdel(&mfd[fd]);
	}
	else
	{
		*line = ft_strdup(mfd[fd]);
		ft_strdel(&mfd[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char *mfd[5000];
	char		buf[BUFF_SIZE + 1];
	int			f;
	char		*s;

	if (fd < 0 || !line || BUFF_SIZE + 1 <= 1 || read(fd, buf, 0) < 0)
		return (-1);
	while ((f = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!mfd[fd])
			mfd[fd] = ft_strnew(0);
		buf[f] = '\0';
		s = ft_strjoin(mfd[fd], buf);
		free(mfd[fd]);
		mfd[fd] = s;
		if (ft_strchr(buf, 10))
			break ;
	}
	if (!mfd[fd] || (f == 0 && mfd[fd][0] == '\0'))
		return (0);
	return (makeline(line, mfd, fd));
}
