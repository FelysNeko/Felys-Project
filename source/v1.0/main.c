#include "header.h"


int
main(int argc, char *argv[])
{
    container raw = {0};
    FILE *file = fopen(argv[1], "r");
    for (int i=0; fgets(raw[i], MAX, file)!=NULL; ++i);

    cmd home; cmdinit(&home);
    cmdparse(&home, raw);
    cmdlist(&home);
    putchar('\n');

    lyr base; lyrinit(&base);
    lyradd(&base);

    
    for (cmd *line=home.next; line!=NULL; ) {
        printf("%p -> ", line);
        while (line->scope > base.next->scope) {
            lyradd(&base);
        }
        while(line->scope < base.next->scope) {
            lyrdlt(&base);
        }

        if (strmatch(line->type, NONE)) {
            rpnexpr(line->expr, &base);
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
        } else if (strmatch(line->type, EXIT)) {
            printf("EOF\n");
            break;
        } else if (strmatch(line->type, GOTO)) {
            line = cmdgoto(&home, (int)rpnexpr(line->expr, &base));
        } else {
            error("UnknownCmd", -1);
        }
        printf("%p\n", line);
    }

    putchar('\n');
    lyrlist(&base);
    
    return 0;
}
