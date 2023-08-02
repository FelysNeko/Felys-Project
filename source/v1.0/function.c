int strlength(char *);
int strmatch(char *, char *);
char *strstrip(char *, char);


int
strmatch(char *a, char *b)
{
    for (int i=0; ; ++i) {
        if (a[i] != b[i]) {
            return FALSE;
        } else if (a[i]==0 && b[i]==0) {
            return TRUE;
        }
    }
}


int
strlength(char *str)
{
    int count = 0;
    for(; str[count]!=0; ++count);
    return count;
}


char *
strstrip(char *str, char c)
{
    int end = strlength(str)-1;
    if (end>-1 && str[end] == c) {
        str[end] = 0;
    }
    return str;
}
