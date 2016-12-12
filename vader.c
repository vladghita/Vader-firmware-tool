#include "vader.h"

/*
   Tool for converting firmware bytes with variable line length
   Please provide input generated with SFK tool
   Outputs a file representing the header file with variable-length structures
   Author: Vlad Ghita (vlad.ghita@orange.com), date 2016/09/11
*/

void main()
{
   int fw_len = sizeof(fw);
   int idx = 0;
   FILE* fp = fopen("firmware.h", "w+");
   
   do
   {
	   //ignore 0x00 chars
	   if(fw[idx] == 0x00)
	   {	   
          idx++;
		  
		  continue;
	   }
	   
	   //first print the table length
	   fprintf(fp, "{%d, {", fw[idx]);
	   
	   //now print the table for current line
	   int tbl = 0;
	   for(tbl = idx + 1; tbl <= idx + fw[idx]; tbl ++)
	   {
		   fprintf(fp, "0x%x", fw[tbl]);
		   if(tbl < idx + fw[idx])
		   {
			   fprintf(fp, ", ");
	       }
	   }
	   
	   fprintf(fp, "}},\n");
	   
	   //fast-forward the index
	   idx += fw[idx] + 1;
	   
   }while(idx < fw_len);
   
   fclose(fp);

   printf("Done. Happy hacking!");
}