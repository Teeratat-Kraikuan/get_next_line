/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkraikua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:56:48 by tkraikua          #+#    #+#             */
/*   Updated: 2022/02/24 13:56:48 by tkraikua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_buff(int fd, char *str)
{
	char	*buff;
	int		byte;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	byte = 1;
	while (byte > 0 && !(char_in_str('\n', str)))
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*read_line(char *str)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[len] != '\n' && str[len] != '\0')
		len++;
	if (str[len] == '\n')
		len++;
	line = (char *) malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*cut_line(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	new_str = (char *) malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str[10000];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = read_buff(fd, str[fd]);
	if (str[fd] == NULL)
		return (NULL);
	line = read_line(str[fd]);
	str[fd] = cut_line(str[fd]);
	return (line);
}
