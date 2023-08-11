#include "../inc/miniRT.h"

t_td_point  get_point(char *name, nType norme)
{
    t_td_point  ret;
    nType       input_norme;
    char        *line;
    
    printf("Input a 3d vector for -%s-\n", name);
    if (norme)
        printf("Will be normalize to %0.2f\n", (float) norme);
    printf("Input x:\t");
    line = get_next_line_nl(0, 0);
    ret.x = ft_atoi(line);
    free(line);
    printf("Input y:\t");
    line = get_next_line_nl(0, 0);
    ret.y = ft_atoi(line);
    free(line);
    printf("Input z:\t");
    line = get_next_line_nl(0, 0);
    ret.z = ft_atoi(line);
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
    if (_min > ret || _max < ret)
        ret = get_number(name, _min, _max);
    return (ret);
}