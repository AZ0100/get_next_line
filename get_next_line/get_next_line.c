/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azourgan <azourgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:58:35 by azourgan          #+#    #+#             */
/*   Updated: 2022/12/04 11:20:24 by azourgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
	static char		*str;
	ssize_t			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	copy = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!copy)
		return (NULL);
	n = 1337;
	while (line_exist(str) == -1 && n > 0)
	{
		n = read(fd, copy, BUFFER_SIZE);
		if (n < 0)
			return (ft_free(copy, &str));
		copy[n] = '\0';
		str = ft_strjoin(str, copy);
		if (!str)
			return (ft_free(copy, &str));
		if (!str[0])
			return (ft_free(copy, &str));
	}
	free (copy);
	return (return_line(&str));
}
