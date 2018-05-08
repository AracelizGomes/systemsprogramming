#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <ctype.h>
#include    <string.h>

int main(int argc, char **argv)
{
    char     buf[1024];
    ssize_t  len;
    int      mode = 't';

    fprintf(stderr, "%s starting ...\n", argv[0]);
    if (argc > 1) {
        mode = argv[1][0];
    }
    if (! mode)
        mode = 't';

    while ((len = read(0, buf, sizeof(buf))) > 0) {
        if (mode == 'l') {
            for (int i = 0; i < len; i ++)
                buf[i] = tolower(buf[i]);
        }
        else if (mode == 'u') {
            for (int i = 0; i < len; i ++)
                buf[i] = toupper(buf[i]);
        }
        else if (mode == 'f') {
            for (int i = 0; i < len; i ++)
                buf[i] = (isalnum(buf[i]) || buf[i] == '\n') ? buf[i] : ' ';
        }
        else {
            for (int i = 0; i < len; i ++)
                if (islower(buf[i]))
                    buf[i] = toupper(buf[i]);
                else if (isupper(buf[i]))
                    buf[i] = tolower(buf[i]);
        }
        write(1, buf, len);
    } 
    return 0;
}
