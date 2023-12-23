#include "felys.h"


cmd *
cmdgoto(cmd *home, int index)
{
    for (cmd *line=home; line!=NULL; line=line->next) {
        if (line->index == index) {
            return line;
        }
    }
    error("LineNotFound", -1);
    return NULL;
}


void
cmdinit(cmd *home)
{
    home->expr = "NO EXPR HERE";
    home->type = "START";
    home->index = 0;
    home->scope = 0;
    home->jump = NULL;
    home->next = NULL;
}


void
cmdparse(cmd *home, container raw)
{
    cmd *line = home;
    for (int i=0; raw[i][0]!=0; ++i) {
        if (!empty(raw[i])) {
            line = cmdread(line, strstrip(raw[i], '\n'), i);
        }
    }

    cmdcheck(home);

    stack end; stkinit(&end);
    stack skip; stkinit(&skip);

    for (line=home->next; line!=NULL; line=line->next) {
        cmd *next = line->next;
        cmd *top = dtoc(stktop(&end));
        cmd *jump = dtoc(stktop(&skip));

        // if while, if, elif reuslt in FALSE, it jump to the next line that have the same scope it has
        if (top!=NULL && strmatch(top->type, WHILE) && top->scope==next->scope) {
            line->jump = top;
            top->jump = next;
            stkpop(&end);
        } else if (top!=NULL && (strmatch(line->type, ELIF) || strmatch(line->type, ELSE)) && top->scope==line->scope) {
            top->jump = line;
            stkpop(&end);
        }

        // after finish if or elif, their last line will jump to the nearest cmd that have same scope as if or elif
        // but the target line cannot have keyword elif or else
        if (!strmatch(line->type, ELIF) && !strmatch(line->type, ELSE)) {
            while (skip.top>-1 && jump!=NULL && line->scope==jump->scope-1) {
                dtoc(stkpop(&skip))->jump = line;
            }
        }
        
        // push if meet condition
        if (strmatch(line->type, IF) || strmatch(line->type, ELIF) || strmatch(line->type, WHILE)) {
            stkpush(&end, (long)line);
        } else if (next!=NULL && (strmatch(next->type, ELIF) || strmatch(next->type, ELSE))) {
            stkpush(&skip, (long)line);
        }
    }
}


static void
cmdcheck(cmd *home)
{
    for (cmd *line=home; line!=NULL; line=line->next) {
        char *type = line->type;
        if (strmatch(type, IF) || strmatch(type, ELIF) || strmatch(type, ELSE) || strmatch(type, WHILE)) {
            if (line->next->scope-1 != line->scope) {
                error("IncorrectTabs", line->index+1);
            }
        }
    }
}


static cmd *
cmdread(cmd *prev, char *str, int index)
{
    cmd *line = (cmd *)malloc(sizeof(cmd));
    prev->next = line;      // link previous cmd to current cmd
    line->index = index+1;
    line->next = NULL;

    // check indentations
    if ((line->scope=tab(str)) == -1) {
        error("IncorrectTabs", index+1);
    }

    // when scope decrease, add an empty cmd to wrap this scope up
    // it's very necessary, because it make interpreter find jump line easier
    for (int diff=prev->scope-line->scope; diff>0; --diff) {
        prev->next = (cmd *)malloc(sizeof(cmd));
        prev = prev->next;
        prev->scope = line->scope + diff;
        prev->type = NONE;
        prev->expr = NONE;
        line->jump = NULL;
        prev->index = -1;   // any cmd added by interpreter have index -1
        prev->next = line;
    }

    char keyword[LEN] = {0};
    int end = loadkw(line->scope*4, str, keyword);  // see where keyword ends and copy it
    line->expr = str+end;   // asume this cmd have keyword, yet the final result

    if (strmatch(keyword, IF)) {
        line->type = IF;
    } else if(strmatch(keyword, ELIF)) {
        line->type = ELIF;
    } else if(strmatch(keyword, ELSE)) {
        line->type = ELSE;
    } else if(strmatch(keyword, WHILE)) {
        line->type = WHILE;
    } else if(strmatch(keyword, EXIT)) {
        line->type = EXIT;
    } else if(strmatch(keyword, GOTO)) {
        line->type = GOTO;
    } else if(strmatch(keyword, SHOW)) {
        line->type = SHOW;
    } else{
        line->type = NONE;
        line->expr = str+line->scope*4; // if no keyword detected, everything will be an expr
    }

    return line;
}


void
cmdlist(cmd *home)
{
    for (cmd *line=home; line!=NULL; line=line->next) {
        printf("[%d]\t<%p> [%d] ", line->index, line, line->scope);
        printf("%8s (%s)", line->type, line->expr);
        if (line->jump != NULL) {
            printf(" -> <%p>", line->jump);
        }
        putchar('\n');
    }
}


static int
loadkw(int start, char *str, char *target)
{
    int count = 0;
    for (; str[start+count]!=' ' && str[start+count]!=0; ++count) {
        target[count] = str[start+count];
    }
    return start+count;
}


static int
tab(char *str)
{
    int count = 0;
    for (; str[count]==' '; ++count);
    int remainder = count%4;

    if (!remainder) {
        return count/4;
    } else{
        return -1;
    }
}


cmd *
dtoc(double x)
{
    return (cmd *)(long)x;
}


static int
empty(char *str)
{
    for (; *str==' ' || *str=='\n'; ++str);
    return *str==0 ? 1 : 0;
}
