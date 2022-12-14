/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azourgan <azourgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:01:36 by azourgan          #+#    #+#             */
/*   Updated: 2022/12/04 11:19:27 by azourgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	line_exist(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*return_line(char **s)
{
	int		i;
	char	*line;
	char	*tmp;

	i = line_exist(*s);
	if (i < 0)
	{
		line = ft_substr(*s, 0, ft_strlen(*s) - 1);
		free(*s);
		*s = NULL;
		return (line);
	}
	line = ft_substr(*s, 0, i);
	tmp = ft_substr(*s, i + 1, ft_strlen(*s) - 1);
	free (*s);
	*s = tmp;
	return (line);
}

char	*ft_free(char *copy, char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
	free (copy);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			*copy;
	static char		*str[OPEN_MAX];
	ssize_t			n;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	copy = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!copy)
		return (NULL);
	n = 1;
	while (line_exist(str[fd]) == -1 && n > 0)
	{
		n = read(fd, copy, BUFFER_SIZE);
		if (n < 0)
			return (ft_free(copy, &str[fd]));
		copy[n] = '\0';
		str[fd] = ft_strjoin(str[fd], copy);
		if (!str[fd])
			return (ft_free(copy, &str[fd]));
		if (!str[fd][0])
			return (ft_free(copy, &str[fd]));
	}
	free (copy);
	return (return_line(&str[fd]));
}
