// Jorge Varea Durán

#include "shell.h"

void parse_redirections(char **args,  char **file_in, char **file_out)
{
    *file_in = NULL;
    *file_out = NULL;
    char **args_start = args;
    while (*args) {
        int is_in = !strcmp(*args, "<");
        int is_out = !strcmp(*args, ">");
        if (is_in || is_out) {
            args++;
            if (*args){
                if (is_in)  *file_in = *args;
                if (is_out) *file_out = *args;
                char **aux = args + 1;
                while (*aux) {
                   *(aux-2) = *aux;
                   aux++;    
                }
                *(aux-2) = NULL;
                args--;
            } else {
                /* Syntax error */
                fprintf(stderr, "syntax error in redirection\n");
                args_start[0] = NULL; // Do nothing
            }
        } else {
            args++; 
        }
    }
    // Debug:
    // *file_in && fprintf(stderr, "[parse_redirections] file_in='%s'\n", *file_in);
    // *file_out && fprintf(stderr, "[parse_redirections] file_out='%s'\n", *file_out);
}

