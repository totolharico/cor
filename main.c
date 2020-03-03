#include "libft/includes/libft.h"
#include <fcntl.h>

int 	main(int ac, char**av)
{
	int	fd;
	int	ret;
	char *line;
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
	}

}
