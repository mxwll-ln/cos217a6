#include <stdio.h>

int main(void)
{
    FILE *psFile;
    psFile = fopen("data", "w");

    /* buf[0 - 18] */
    fprintf(psFile, "Maxwell and Melody");
    return 0;
}