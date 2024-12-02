/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-01 13:22:32 by ynoujoum          #+#    #+#             */
/*   Updated: 2024-12-01 13:22:32 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	char	*reset_ptr(char *ptr)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = NULL;
	while (ptr[i] != '\0' && ptr[i] != '\n')
		i++;
	if (ptr[i] == '\0')
		return (free(ptr), ptr = NULL, NULL);
	i++;
	while (ptr[i + j] != '\0')
		j++;
	tmp = malloc((sizeof(char) * (j + 1)));
	if (!tmp)
		return (free(ptr), ptr = NULL, NULL);
	ft_strcpy(tmp, &ptr[i]);
	free(ptr);
	ptr = NULL;
	return (tmp);
}

static	char	*get_line(char *str)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static	char	*create_line(char *ptr, int fd)
{
	char	*buffer;
	int		chars_read;

	buffer = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buffer)
		return (free(ptr), ptr = NULL, NULL);
	if (!ptr)
		ptr = ft_strdup("");
	while (ptr && !check_new_line(ptr))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			if (chars_read < 0)
				return (free(buffer), buffer = NULL, NULL);
			return (free(buffer), buffer = NULL, ptr);
		}
		buffer[chars_read] = '\0';
		ptr = ft_strjoin(ptr, buffer);
		if (!ptr)
			return (free(buffer), buffer = NULL, NULL);
	}
	free(buffer);
	buffer = NULL;
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*ptr[OPEN_MAX] = {NULL};
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647
		|| fd < 0 || read(fd, line, 0) < 0)
		return (free(ptr[fd]), ptr[fd] = NULL, NULL);
	ptr[fd] = create_line(ptr[fd], fd);
	if (!ptr[fd] || ptr[fd][0] == '\0')
	{
		free(ptr[fd]);
		ptr[fd] = NULL;
		return (NULL);
	}
	line = get_line(ptr[fd]);
	if (line == NULL)
	{
		free(ptr[fd]);
		ptr[fd] = NULL;
		return (NULL);
	}
	ptr[fd] = reset_ptr(ptr[fd]);
	return (line);
}
