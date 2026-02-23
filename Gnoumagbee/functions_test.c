#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *r;
    //char *pwd;

    //pwd = getcwd(NULL, 0);
    //printf("%s\n", r);
    r = readline("Prompt > ");
    rl_replace_line("hihi", 0);
    rl_redisplay();
    printf("%s\n", r);
    //add_history(r);
    //printf("History : %s\n", add_history(r));
    free(r);
    return(0);
}