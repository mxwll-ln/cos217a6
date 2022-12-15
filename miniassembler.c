/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   int bitmask;
   int intermediate;

   /* create bitmask */
   bitmask = 1;
   bitmask = bitmask << uiNumBits;
   bitmask--;

   /* isolate source copy bits */
   bitmask = bitmask << uiSrcStartBit;
   intermediate = uiSrc & bitmask;

   /* shift bits on top of destination target */
   intermediate = intermediate << (uiDestStartBit - uiSrcStartBit);

   /* set destination target bits */
   *puiDest = *puiDest | intermediate;
}

/*
001001010110111111010 source
&
000000000011110000000 mask
=
000000000010110000000 selected source bits

<< >> align 

|
010101111101001010101 dest
=
010101111111111010101 final
*/

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   unsigned int uiInstr;

   /* Base Instruction Code (0101 0010 1---)*/
   uiInstr = 0x52800000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* immediate value to be moved */
   setField(iImmed, 0, &uiInstr, 5, 16);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int uiInstr;

   /* Base Instruction Code (0011 1001 00--)*/
   uiInstr = 0x39000000;

   setField(uiFromReg, 0, &uiInstr, 0, 5);
   setField(uiToReg, 0, &uiInstr, 5, 10);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x14000000;

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);
   printf("%x\n", uiDisp);
   setField(uiDisp, 2, &uiInstr, 0, 26);

   return uiInstr;
}