#include "header.h"


int
main(int argc, char *argv[])
{
    int verbose = argc==3 && strmatch(argv[2], "debug") ? TRUE : FALSE;

    // read file and save in raw
    container raw = {0};
    FILE *file = fopen(argv[1], "r");
    for (int i=0; fgets(raw[i], MAX, file)!=NULL; ++i);

    // parse all cmd
    cmd home; cmdinit(&home);
    cmdparse(&home, raw);
    if (verbose) {
        cmdlist(&home);
        putchar('\n');
    }

    // create variable layers
    lyr base; lyrinit(&base);
    lyradd(&base);
    
    // execuate
    for (cmd *line=home.next; line!=NULL; ) {
        if (verbose) printf("%p -> ", line);
        // in case a jump in scope caused by goto, loop it
        while (line->scope > base.next->scope) {
            lyradd(&base);
        }
        while(line->scope < base.next->scope) {
            lyrdlt(&base);
        }

        if (strmatch(line->type, NONE) || strmatch(line->type, SHOW)) {
            double reuslt = rpnexpr(line->expr, &base);
            if (strmatch(line->type, SHOW) && !verbose){
                printf("%f\n", reuslt);
            }
            if (line->jump == NULL) {
                line = line->next;
            } else{
                line = line->jump;
            }
        } else if (strmatch(line->type, ELSE)) {
            line = line->next;
        } else if (strmatch(line->type, WHILE) || strmatch(line->type, IF) || strmatch(line->type, ELIF)) {
            if (rpnexpr(line->expr, &base)) {
                line = line->next;
            } else{
                line = line->jump;
            }
        } else if (strmatch(line->type, GOTO)) {
            line = cmdgoto(&home, (int)rpnexpr(line->expr, &base));
        } else if (strmatch(line->type, EXIT)) {
            if (verbose) printf("EOF\n");
            break;
        } else {
            error("UnknownCmd", -1);
        }
        if (verbose) printf("%p\n", line);
    }

    if (verbose) {
        putchar('\n');
        lyrlist(&base);
    }
    
    return 0;
}
