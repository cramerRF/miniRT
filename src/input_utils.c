#include "../inc/miniRT.h"

t_td_point  get_point(char *name, nType norme)
{
    t_td_point  ret;
    nType       input_norme;
    char        *line;
    
    printf("Input a 3d vector for -%s-\n", name);
    if (norme)
        printf("Will be normalize to %0.2f\n", (float) norme);
    printf("Input x:\n");
    line = get_next_line_nl(0, 0);
    ret.x = atof(line);
    free(line);
    printf("Input y:\n");
    line = get_next_line_nl(0, 0);
    ret.y = atof(line);
    free(line);
    printf("Input z:\n");
    line = get_next_line_nl(0, 0);
    ret.z = atof(line);
    free(line);
    if (!ret.x && !ret.y && !ret.z)
        return (get_point(name, norme));
    if (norme)
    {
        input_norme = sqrt(ret.x * ret.x + ret.y * ret.y + ret.z * ret.z);
        ret.x = (ret.x / input_norme) * norme;
        ret.y = (ret.y / input_norme) * norme;
        ret.z = (ret.z / input_norme) * norme;
    }
    return (ret);
}

nType   get_number(char *name, nType _min, nType _max)
{
    nType   ret;
    char        *line;
    
    if (_min >= _max)
        return (printf("Error: get_number _min > _max\n"), 0);
    printf("Input a number for -%s- between %0.2f and %0.2f:\n", name, (float) _min, (float) _max);
    line = get_next_line_nl(0, 0);
    ret = ft_atoi(line);
    free(line);
    if (_min >= ret || _max <= ret)
        ret = get_number(name, _min, _max);
    return (ret);
}

int line_to_point(char *line, t_td_point *p)
{
    int     len;
    char    **split;

    if (!line)
        return (printf("Error null line\n"), 1);
    split = ft_split(line, ',');
    len = 0;
    while (split[len])
        len++;
    if (len != 3)
        return (printf("Error %d len should be 3\n", len), ft_free_split(split), 1);
    p->x = atof(split[0]);
    p->y = atof(split[1]);
    p->z = atof(split[2]);
    ft_free_split(split);
    return (0);
}
