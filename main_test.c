#include "inc/minishell.h"
#include "Libft/inc/libft.h"

int main(int ac, char **av)
{
    int i = 0;
    printf("ac : %d\n", ac);
    while(av[i])
    {
        printf("av[%d] : %s\n", i, av[i]);
        i++;
    }
    // printf("after del : %s\n", str2);
    // char *str = "|Bonjour";
    // char *str2 = "|";
    // i = ft_strncmp(str2, str, ft_strlen(str));
    // printf("res : %d\n", i);
    // int i = 0;
    // int k = 0;
    // while(i < 5)
    // {
    //     printf("i : %d\n", i);
    //     printf("k : %d\n", k);
    //     k++;
    //     if(k == 2)
    //         continue;
    //     i++;
    // }
    // printf("______________\n");
    // printf("i : %d\n", i);
    // printf("k : %d\n", k);
}
