#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int 	fd;
	int		ret;
	char	*line;

	fd = open("./Makefile", O_RDONLY);
	assert(fd != -1);
	line = 0;
	while ((ret = ft_get_next_line(fd, &line)))
	{
		if (line)
		{
			ft_putendl(line);
			free(line);
			line = NULL;
		}
	}
	if (line)
	{
		ft_putendl(line);
		free(line);
	}
	close(fd);
	return (0);
}
