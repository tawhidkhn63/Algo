#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ltrim(char *s) {
	while (*s == ' ' || *s == '\t') s++;
	return s;
}

char getRegister(char *text) {
	if (*text == 'r' || *text=='R') text++;
	return atoi(text);
}

int getConstant(char *text){
	return atoi(text);
}

int assembleLine(char *text, unsigned char* bytes) {
	text = ltrim(text);
	char *keyWord = strtok(text," ");

	//----------------Add----------------//
	if (strcmp("add",keyWord) == 0) {
		bytes[0] = 0x10;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));

		return 2;
	}

	//--------------Subtract--------------//
	if(strcmp("subtract", keyWord) == 0){
		bytes[0] = 0x50;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));

 		return 2;
	}

	//--------------Multiply--------------//
	if(strcmp("multiply", keyWord) == 0){
		bytes[0] = 0x40;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
 		return 2;
	}

	//--------------Divide--------------//
	if(strcmp("divide", keyWord) == 0){
		bytes[0] = 0x30;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));

 		return 2;
	}

	//----------------And----------------//
	if(strcmp("and", keyWord) == 0){
		bytes[0] = 0x20;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		
 		return 2;
	}

	//----------------Or----------------//
	if(strcmp("or", keyWord) == 0){
		bytes[0] = 0x60;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		
 		return 2;
	}

	//---------------Halt---------------//
	if(strcmp("halt", keyWord) == 0){
		bytes[0] = 0x00;

		return 2;
	}

	//---------------------------------------------------------------------------//


	//---------------Call---------------//
	if(strcmp("call", keyWord) == 0){	
		long bits = getConstant(strtok(NULL," "));

		bytes[0] = 0xD0;
		bytes[0] |= 0xF000000 & bits >> 24;
		bytes[1] = 0x0FF0000 & bits >> 16;
		bytes[2] = 0X000FF00 & bits >> 8;
		bytes[3] = 0x00000FF & bits;

		return 4;
 	}

 	//---------------Jump---------------//
 	if(strcmp("jump", keyWord) == 0){	
		long bits = getConstant(strtok(NULL," "));

		bytes[0] = 0xC0;
		bytes[0] |= 0xF000000 & bits >> 24;
		bytes[1] = 0x0FF0000 & bits >> 16;
		bytes[2] = 0X000FF00 & bits >> 8;
		bytes[3] = 0x00000FF & bits;

		return 4;
 	}

	//---------------------------------------------------------------------------//

 	//---------------Branchifequal---------------//
 	if (strcmp("branchifequal", keyWord) == 0) {
 		long register1 = getRegister(strtok(NULL," "));
		long register2 = getRegister(strtok(NULL," ")); 

		long bits = getConstant(strtok(NULL," ")); 

		bytes[0] = 0xA0; 
		bytes[0] |= register1; 
		bytes[1] = register2 << 4;
		bytes[1] |= (0xF0000 & bits) >> 16;
		bytes[2] = (0x0FF00 & bits) >> 8;
		bytes[3] = (0x000FF & bits); 

		return 4;
	}

	//---------------Branchifless---------------//
 	if(strcmp("branchifless", keyWord) == 0){	
		long register1 = getRegister(strtok(NULL," "));
		long register2 = getRegister(strtok(NULL," ")); 

		long bits = getConstant(strtok(NULL," ")); 

		bytes[0] = 0xB0; 
		bytes[0] |= register1; 
		bytes[1] = register2 << 4;
		bytes[1] |= (0xF0000 & bits) >> 16;
		bytes[2] = (0x0FF00 & bits) >> 8;
		bytes[3] = (0x000FF & bits); 

		return 4;
 	}

 	//---------------------------------------------------------------------------//

 	//---------------Addimmediate---------------//
 	if(strcmp("addimmediate", keyWord) == 0){	
		long register1 = getRegister(strtok(NULL," "));

		long bits = getConstant(strtok(NULL," ")); 

		bytes[0] = 0x90; 
		bytes[0] |= register1;
		bytes[1] = bits;

		return 2;
 	}

 	//---------------------------------------------------------------------------//

 	//---------------Pop---------------//
 	if(strcmp("pop", keyWord) == 0){	
		long register1 = getRegister(strtok(NULL," "));

		bytes[0] = 0x70; 
		bytes[0] |= register1;
		bytes[1] = 0x80;

		return 2;
 	}

 	//---------------Push---------------//
 	if(strcmp("push", keyWord) == 0){	
		long register1 = getRegister(strtok(NULL," "));

		bytes[0] = 0x70; 
		bytes[0] |= register1;
		bytes[1] = 0x40;

		return 2;
 	}

 	//---------------Return---------------//
 	if(strcmp("return", keyWord) == 0){	
		long register1 = getRegister(strtok(NULL," "));

		bytes[0] = 0x70; 
		bytes[0] |= register1;
		bytes[1] = 0x00;

		return 2;
 	}

 	//---------------------------------------------------------------------------//

 	//---------------Interrupt---------------//
 	if(strcmp("interrupt", keyWord) == 0){	 

 		long bits = getConstant(strtok(NULL," "));

		bytes[0] = 0x80; 
		bytes[1] = bits;

		return 2;
 	}

 	//---------------------------------------------------------------------------//

 	//---------------Store---------------//
 	if(strcmp("store", keyWord) == 0){	

 		long register1 = getRegister(strtok(NULL," "));
		long register2 = getRegister(strtok(NULL," ")); 

		long bits = getConstant(strtok(NULL," "));


		bytes[0] = 0xF0; 
		bytes[0] |= register1; 
		bytes[1] = register2 << 4;
		bytes[1] |= bits; 

		return 2;
 	}

 	//---------------Load---------------//
 	if(strcmp("load", keyWord) == 0){	

 		long register1 = getRegister(strtok(NULL," "));
		long register2 = getRegister(strtok(NULL," ")); 

		long bits = getConstant(strtok(NULL," "));


		bytes[0] = 0xE0; 
		bytes[0] |= register1; 
		bytes[1] = register2 << 4;
		bytes[1] |= bits; 

		return 2;
 	}

}


int main(int argc, char **argv) {
	FILE *src = fopen(argv[1],"r");
	FILE *dst = fopen(argv[2],"w");
	while (!feof(src)) {
		unsigned char bytes[4];
		char line[1000];
		if (NULL != fgets(line, 1000, src)) {
			printf ("read: %s\n",line);
			int byteCount = assembleLine(line,bytes);
			fwrite(bytes,byteCount,1,dst);
		}
	}
	fclose(src);
	fclose(dst);
	return 0;
}