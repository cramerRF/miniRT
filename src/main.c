#include    "../inc/miniRT.h"

int main(int argc, char **args)
{
    t_rt    *rt;
    char    *line;

    if (argc == 2)
        rt = open_rt_file(args[1]);
    else
        return (help_use(), 1);
    while (1)
    {
        //read commands
        printf("Reading comands\n");
        help    help_command();
        add     add_menu();
        delete  delete_menu();  
        edit    edit_menu();  
    }
    return (0);
}