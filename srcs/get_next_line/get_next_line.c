#include "libft.h"

static char	*_ft_gnl_join(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		len;
	char	*s;

	if (!s1 && !s2)
		return (0);
	s1_len = s1 ? ft_strlen(s1) : 0;
	s2_len = s2 ? ft_strlen(s2) : 0;
	len = s1_len + s2_len;
	s = LIBFT_MALLOC(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	ft_memmove(s, s1, s1_len);
	ft_memmove(s + s1_len, s2, s2_len);
	s[len] = '\0';
	LIBFT_FREE((char *)s1);
	return (s);
}

static int	_ft_gnl_find_endl(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}

static char	*_ft_gnl_save_string(char *str)
{
	char	*dest;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		LIBFT_FREE(str);
		return (NULL);
	}
	if (!(dest = LIBFT_MALLOC(sizeof(char) * (ft_strlen(str) - i) + 1)))
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	LIBFT_FREE(str);
	return (dest);
}

static char	*_ft_gnl_create_line(char *str)
{
	char	*line;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(line = LIBFT_MALLOC(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	ft_get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*str[256];
	int			nb_read;

	if (fd < 0 || !line || LIBFT_BUFFERSIZE <= 0)
		return (-1);
	if (!(buffer = LIBFT_MALLOC(sizeof(char) * LIBFT_BUFFERSIZE + 1)))
		return (-1);
	nb_read = 1;
	while (!_ft_gnl_find_endl(str[fd]) && nb_read != 0)
	{
		if ((nb_read = read(fd, buffer, LIBFT_BUFFERSIZE)) == -1)
		{
			LIBFT_FREE(buffer);
			return (-1);
		}
		buffer[nb_read] = '\0';
		str[fd] = _ft_gnl_join(str[fd], buffer);
	}
	LIBFT_FREE(buffer);
	*line = _ft_gnl_create_line(str[fd]);
	str[fd] = _ft_gnl_save_string(str[fd]);
	return (nb_read == 0 ? 0 : 1);
}
