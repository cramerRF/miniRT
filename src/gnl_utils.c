#include "../inc/miniRT.h"

char	*get_next_line_nl(int fd, int flag)
{
	char	*line;

	if (flag)
		return (get_next_line(fd));
	line = get_next_line(fd);
	if (line && line[ft_strlen(line) - 1] == '\n')
        line[ft_strlen(line) - 1] = 0;
    return (line);
}