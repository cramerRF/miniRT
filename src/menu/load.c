#include "../../inc/miniRT.h"

int rt_load(t_rt *rt)
{
    char    *input;
    char    *file;

    printf("rt_load %p file: %s\nSure you want to load this file? (Y/N) Y\n", rt, rt->file);
    file = NULL;
    input = get_next_line_nl(0, 0);
    if (input && (!ft_strncmp(input, "N", 2) || !ft_strncmp(input, "n", 2)))
    {
        printf("Input file name:\n");
        file = get_next_line_nl(0, 0);
    }
    if (input)
        free(input);
    if (!file)
        file = ft_strdup(rt->file);
    rt_exit(rt);
    *get_rt_addr(NULL) = open_rt_file(file);
    free(file);
    if (!rt)
        return (printf("Error during open_rt_file\n"), 1);
    return (0);
}