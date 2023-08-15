#include "../../inc/miniRT.h"

int rt_load(t_rt *rt)
{
    char    *input;
    char    *file;
    t_rt    *aux;

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
    aux = open_rt_file(file);
    if (!aux)
        return (printf("Error during open_rt_file\n"), free(file), 1);
    rt_exit(rt);
    *(get_rt_addr(NULL)) = aux;
    free(file);
    if (!*(get_rt_addr(NULL)))
        return (printf("Error during open_rt_file\n"), 1);
    return (0);
}