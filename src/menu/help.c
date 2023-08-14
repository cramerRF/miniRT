#include "../../inc/miniRT.h"

int 		rt_help(t_rt *rt)
{
    printf("Help panel %p\n", rt);
    printf("\tADD | add | a\t\t\tAdd a new object\n");
    printf("\tEDIT | edit | e\t\t\tEdit existing object\n");
    printf("\tDELETE | delete | del | d\tDelete existing object\n");
    printf("\tEXIT | exit\t\t\tExit program\n");
    printf("\tHELP | help\t\t\tHelp panel\n");
    printf("\tLIST | list | ls\t\tList existing objects\n");
    printf("\tSAVE | save \t\t\tSave scene to file\n");
    printf("\tLOAD | load \t\t\tLoad scene from file\n");
    printf("\tRENDER | render\t\t\tRender scene\n");
    return (0);
}