#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{ 
	char byte_written,*byte_read,dummy;
  	FILE * MEM;
	size_t result;

        byte_read=(char*)(malloc(3));
        /* Reading from memory driver */
	MEM = fopen("/dev/memory", "rb");
        printf("enter characters\n");
        scanf("%c",&dummy);
  	result = fread(byte_read,1,3,MEM);	
  	printf("Byte value read is %s\n",byte_read);
	printf("Number of bytes read is %d\n",result);

  	fclose(MEM);




 	/* Opening the memory driver */
 	MEM=fopen("/dev/memory","wb");

	/* No buffering for file i/o */
  	setvbuf(MEM,&dummy,_IONBF,1);

  	/* Initializing byte_written */
  	
	
   
  	/* Writing to the memory driver */
  	printf("Byte value written is %s\n",byte_read);
  	fwrite(byte_read,1,3,MEM);
	fclose (MEM);

	
}
