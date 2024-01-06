#include "../../inc/miniRT.h"

int rt_render(t_rt *rt)
{
    char    *line;

    printf("rt_render %p\n", rt);
    while (1)
    {
        printf("MENU\n\t-add\n\t-edit\n\t-update\n\t-exit\n");
        line = get_next_line_nl(0, 0);
        if (!ft_strncmp(line, "add", 4) && rt_render_add(rt))
            break ;
        else if (!ft_strncmp(line, "edit", 5) && rt_render_edit(rt))
            break ;
        else if (!ft_strncmp(line, "update", 7) && rt_render_update(rt))
            break ;
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        if (line)
            free(line);
    }
    if (line)
        free(line);
    return (0);
}