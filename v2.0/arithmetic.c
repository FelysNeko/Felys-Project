#include "felys.h"


char *
complement(char *data, size_t size)
{
    char *result = CALLOC(size-1, char);
    if (data[0] == '+') {
        for (int i=0; i<size-1; ++i) {
            result[i] = data[i+1];
        }
    } else if (data[0]=='-' && size>=2) {
        for (int i=size-2, temp, carry=1; i>=0; --i) {
            if ((temp = char_to_int(data[i+1])) == '.') {
                result[i] = temp;
                continue;
            }
            temp = 9 - temp + carry;
            if ((carry = (temp >= 10))) {
                temp %= 10;
            }
            result[i] = int_to_char(temp);
        }
    } else {
        raise("failed to complement");
    }
    return result;
}