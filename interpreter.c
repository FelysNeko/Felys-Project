#include <stdio.h>
#include "functions.c"

int main(int argc, char *argv[]){
    char *path;
    if (argc == 2){
        path = argv[1];
    } else{
        return -1;
    }

    char command[MAX] = {0};
    float ans;
    FILE *fptr = fopen(path, "r");
    variables data; initvar(&data);
    rpn container; initrpn(&container);

    int assign;
    char varname[LEN];
    while (fgets(command, MAX, fptr) != NULL){
        initrpn(&container);
        assign = 0;
        for (int i=0; command[i]!=0; ++i){
            switch (command[i]){
                case '=': assign = i+1; break;
                case '\n': command[i] = 0; break;
            }
        }

        postfix(&container, &command[assign]);
        // printf("Line parsed: ");
        // showrpn(container);
        ans = calculate(container, data);
        
        if (assign){
            for (; type(command[assign-2]); --assign);
            int i = 0;
            for (; i < assign-1; ++i){
                varname[i] = command[i];
            }
            varname[i] = 0;
            addvar(&data, varname, ans);
        } else{
            printf("%f\n", ans);
        }
    }
    return 0;
}