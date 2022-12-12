#include <stdio.h>

void main()
{
    FILE *psFile;
    psFile = fopen("data", "w");

    fprintf(psFile, "Maxwell and Melody");  // buf[0 - 18]
}