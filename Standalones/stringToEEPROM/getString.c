#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Max 1000		/*maximum size of array containing the chars of the strings*/
#define tab 9
#define newLine 10
#define offset 100

FILE *readptr;	/*pointe to read and write from files.*/
int i = 0;
int j = 0;
int count = 0;
int strMax;				
int strings[Max];		/*Array containing all of the strings which will be written to EEPROM*/
int names[Max / 4];		/*An array containing all of the names of each string*/
int stringStartPositions[Max / 10];	/*an array containing the start positions of each each string that was going to be written into EEPROM*/
char currentChar;
int output = 1; //1 for second file 0 for other
int writingName = 1; //1 = writing name, 0 = writing string

void readFile(void);
void writeFile(void);


void main(void)
{
	readFile();
	readptr = fopen("output.txt", "w");

	writeFile();
	output = 0;
	readptr = fopen("output2.txt", "w");
	writeFile();
}

void readFile(void)
{
	stringStartPositions[0] = offset;	/*Sets the first string location to an offset*/
	readptr = fopen("Strings.txt", "r");	/*Sets the pointer to start of text file Strings.txt for reading*/
	while (currentChar != -1)		/*While the end of the file is not read, loop through.*/
	{
		currentChar = fgetc(readptr);	/*set currentChar = to the next char in the file*/

		/*writingName is high until a tab is received, and then set low for writing the string*/
		if (writingName)	/*While still reading the name, store the char in the names array*/
		{
			names[j] = currentChar;
			j++;
		}
		else{	/*otherwise store in the strings array*/
			strings[i] = currentChar;
			i++;
		}
		if (currentChar == tab)writingName = 0;		/*If currentChar = to tab, set writing name low, meaning strings*/
		if (currentChar == newLine)		/*If reached the end of the line, reset writing name and store position in stringPositions array*/
		{
			writingName = 1;
			count++;
			stringStartPositions[count] = (i + offset);
		}
	}
	strings[i - 1] = 0;/*Removes last char receieved as it is eof and not wanted to store in eeprom*/
}


void writeFile()
{
	i = 0;
	fprintf(readptr, "Data to be entered into eeprom at location 0x%X: \n", offset); /*Explains where all this data will be stored from*/
	while (strings[i])	/*Lists all the strings that will be stored*/
	{
		fprintf(readptr, "%c", strings[i]);
		i++;
	}
	strMax = i;	/*Sets max position of writing*/
	fprintf(readptr, "\n#define ");
	i = 0;
	j = 0;
	count = 0;
	while (names[i])/*Write define, name string and address into 2 files for ease of use*/
	{
		if (names[i] == tab)
		{
			if (!output){
				fprintf(readptr, " \"");/*Prints string if writing to certain file*/
				while (strings[j] != newLine && j < strMax)/*loop through string, writing each char*/
				{
					fprintf(readptr, "%c", strings[j]);
					j++;

				}
			}
			if (output){	/*Print of #define and location of previous string*/
				fprintf(readptr, " 0x");
				fprintf(readptr, "%X\n#define ", stringStartPositions[count]);
			}	
			else{			/*Print of #define and end of quotations "*/
				fprintf(readptr, "\"\n");
				fprintf(readptr, "#define ");
			}
			count++;	/*increment*/
			j++;
		}
		else{
			fprintf(readptr, "%c", names[i]);
		}
		i++;
	}
	fclose(readptr);
}
