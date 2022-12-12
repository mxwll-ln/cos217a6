#include <stdio.h>

int main(void)
{
    FILE *psFile;
    psFile = fopen("dataB", "w");

    /* buf[0 - 17] */
    fprintf(psFile, "Maxwell and Melody");
    /* buf[18] */
    fprintf(psFile, "%c", '\0');
    /* buf[19-47] */
    fprintf(psFile, "fillerfillerfillerfillerfill");
    return 0;
}