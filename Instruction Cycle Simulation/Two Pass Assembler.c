#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Includes the necesary files


struct  data{
//Creates a structure that will hold the data of a varible given by the instruction


	int num;
	//Will hold the sybols number 
	
	
	int index;
	//Will hold the index of the number
	
	
	int boolean;
	//Will be a check to see if the variable has a value or is just a label
	
	
	char label[10];
	//Will hold the label for the variable

	
};


char machInstr[50][25];
//Creates an array of strings to hold the machine instructions created in the program


char unknownInstr[50][25];
//Creates an array of strings to hold the undefined instruction


char multiInstr[50][25];
//Creates an array of strings to hold the multipliy defined operands


char instr[50][256];
//Creates an array of strings to hold read in instructions


int unknownCount = 0;
//Holds the number of unknown instructions


int unknownIndex[50];
//Holds the indexs of the unknown instructions


int multiCount = 0;
//Holds the number of multiple instructions


int multiIndex[50];
//Holds the indexs of the multiple instructions


int multiBoolean = 0;
//Signals whether or not there is a an instance of a multiple definition

int memoryAddress[50];
//Hold an array of indexs that contain memory locations


int memCount = 0;
//Holds the number of indexs that contain memory locations


char symTable [50][256];
//Creates an array of string to hold the symbol table


struct data variables[50];
//Creates an instance of the structure


void pass(int passedIn);
//Will go through a non-jump command and build its machine code instruction


void jumpPass(int passedIn);
//Will go through a jump command and build its machine code instruction*


char* itoa(int num, char* str, int base);
//Creates the itoa method for Unix


char* reverse_string(char *str);
//Creates a reverse string method, in place of strrev which doesnt compile on unix


int main(int argc, char *argv[]) {
	
	
	FILE *inputFile;
	//The file object that will hold the file where instructions are to be read in from
	
	
	inputFile = fopen("proj1b.dat", "r");
	//opens the input file and gives the program permission to read data in from it	
	
		
	int i = 0;
	//Takes the counter from the loop that was passed in and stores it in i
	
	
	int j = 0;
	//Holds the counter for the conversion while loop
	
	
	int k = 0;
	//Holds the index of operand during the while loop
	
	
	int l = 0; 
	//Holds the index of the operand for a variable
	
	
	int m = 0; 
	//Holds the index of the structure variable
	
	
	int sizeOf = -1;
	//Holds the number of bits set in the operand
	
	
	char operand [13];
	//Holds the operand portion of the instruction
	
	
	char binNum [10];
	//Holds the converted binary number
	
	
	char label [10];
	//Creates a char array to hold the passed in label of the variable
	
	
	
	while(m < 50){		
		
		
		variables[m].label[0] = ' ';
		
		variables[m].label[1] = ' ';
		
		variables[m].index = 0;
		
		variables[m].num = 0;
		
		variables[m].boolean = 0;
		//Intitalizes all data in the structure object
		
		m++;
		
		
	}
	
	
	m = 0;
	//Sets m to zero for later use
	
	
	
	while(i < 50){
		
		
		if(fgets(instr[i], 256, inputFile) != NULL){
		//Assigns the line of input from the file to instr and checks if it is null	
		
			
			if(instr[i][0] != ' ' &&  instr[i][0] != '\0'){
			//Checks to see if the instruction has a label

				
				while(instr[i][j] != ' ' & instr[i][j] != ','){
				//Will go through and get the label of the instruction
				
				
					symTable [k][j] = instr[i][j];
					//Builds the symbol table with the label of the instruction
					
					
					j++;
					
					
				}//end while loop
			
				for(j = 0; j < 50; j++){
					
					if(strcmp(symTable [k], variables[j].label) == 0) {
					//Checks to see if their are multiple declaration of an operand
				
						multiBoolean = 1;
						//Singalls there is a repeat instruction
						
					}
					
				}
					
				
				if(multiBoolean == 0){
					
					
					for(j = 0; j < 4; j++){
					//Goes to 4 as biggest label will be LOOP
						
						variables[m].label[j] = symTable [k][j];
						//Loads the symbol into the structure to later build the symbol table		
									
						
					}				
					
					variables[m].index = i+1;
					//Sets the location of the symbol to index and stores it in the structure	
				
				}
				
				
				else {
				
		
					for(k = 0; k < 50; k++){
						
						multiInstr[multiCount][k] = instr[i][k];
						//Loads the instruction into the multiple array
					
					}
						
					multiIndex[multiCount] = i;
			        //Stores the index of the repeated instruction
			        
			        
					multiCount++;
					//Increments multiCount to show another instruction has been added to this array
					
					
					for(j = 8; j < 16; j++) {
			
						machInstr[i][j] = 'M';
						//Sets M values to the machine code instruction
			
					}	
						
				}
				
	
				j=0;
				//Sets j back to zero for later use
				
				multiBoolean =0;
				//Resets multiBoolean back to zero
				
				k++;
				//Increments k so it can be used for the next label
				
				m++;
				
			}
			
			
			if(strstr(instr[i], ".dw") != NULL) {
			//Proceeds if a define with word quantity command was read in			
				
				
				j = 11;
				l = 11;
				//Sets l and j to the index of the operand
				
				
				while(instr[i][j] != ' ' && instr[i][j] != '\0' && instr[i][j] != '\n'){
						
						
					operand[(11 - l)] = instr[i][j];
					//loads the array with the operand
				
					
					j++;
					//Increments j to the index of the next instruction
					
					
					l--;
					//Decrements j to get the index of the next operand character
						
						
				}//end while loop	
						
			
				
				variables[m].num = atoi(operand);
				//Converts the operand into a decimal number and stores it in the structure
				
				
				variables[m].boolean = 1;
				//Signals this data has a value
				
				
				j = 0;
				//sets j to zero for later use
				
				
				for(l = 0; l < 12; l++){
		
							
					operand[l] = ' ';
					//Clears the operand for the next use
							
							
				}
				
				m++;
				//Increments m to hold the index of the next variable
		
			}//end variable declaration if statements			
		}
		
		i++;
				
	}//end first pass while loop
	
	
	
	i = 0;
	//Sets i to one to skip first instruction 
	
	for(i = 0; i < 50; i++){
		
		
		printf("%s", variables[i].num);
		
		
	}
	rewind(inputFile);
	//Goes back to the beginning of the input File to be read from the start again
	
	
	
	FILE *outputFile; 
	//File object that will hold the output file
	
	
	outputFile = fopen("proj1b.out", "w+");
	//Creates a file for output to be written on
	
	
	
	while(i < 50){

	
		if(fgets(instr[i], 256, inputFile) != NULL){
		//Assigns the line of input from the file to instr and checks if it is null	

		if(i > 0){
		//Will run through the loop after skipping the first instruction
		
			if(strstr(instr[0], ".st") == NULL) {
			//Proceeds if the first instruction read does not contain a start command
			
			
			
				printf("Input File Does Not Have Start Command!!");
				//prints an error message if ".st" is not in the file
				
				
			}
			
			
			
			else if(strstr(instr[i], "LOD") != NULL) {
			//Proceeds if the passed in line had a load command 

				machInstr[i][0] = '0';
				machInstr[i][1] = '0';
				machInstr[i][2] = '0';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end LOD if statements
			
			
			else if(strstr(instr[i], "STO") != NULL) {
			//Proceeds if the passed in line had a store command
			
				machInstr[i][0] = '0';
				machInstr[i][1] = '0';
				machInstr[i][2] = '0';
				machInstr[i][3] = '1';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end STO if statements
			
			
			else if(strstr(instr[i], "ADD") != NULL) {
			//Proceeds if the passed in line had a add command
			
				machInstr[i][0] = '0';
				machInstr[i][1] = '0';
				machInstr[i][2] = '1';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end ADD if statements
			
			
			else if(strstr(instr[i], "SUB") != NULL) {
			//Proceeds if the passed in line had a subtract command
			
			
				machInstr[i][0] = '0';
				machInstr[i][1] = '0';
				machInstr[i][2] = '1';
				machInstr[i][3] = '1';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end SUB if statements
			
			
			else if(strstr(instr[i], "ADR") != NULL) {
			//Proceeds if the passed in line had a add command for a given register			
		
				machInstr[i][0] = '0';
				machInstr[i][1] = '1';
				machInstr[i][2] = '0';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end ADR if statements
			
			
			else if(strstr(instr[i], "SUR") != NULL) {
			//Proceeds if the passed in line had a subtract command for a given register
			
			
				machInstr[i][0] = '0';
				machInstr[i][1] = '1';
				machInstr[i][2] = '0';
				machInstr[i][3] = '1';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end SUR if statements
			
			
			else if(strstr(instr[i], "AND") != NULL) {
			//Proceeds if the passed in line had a AND command
			
			
				machInstr[i][0] = '0';
				machInstr[i][1] = '1';
				machInstr[i][2] = '1';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end AND if statements
			
			
			else if(strstr(instr[i], "IOR") != NULL) {
			//Proceeds if the passed in line had a or command
				
			
				machInstr[i][0] = '0';
				machInstr[i][1] = '1';
				machInstr[i][2] = '1';
				machInstr[i][3] = '1';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end IOR if statements
			
			
			else if(strstr(instr[i], "NOT") != NULL) {
			//Proceeds if the passed in line had a not command
				
			
				machInstr[i][0] = '1';
				machInstr[i][1] = '0';
				machInstr[i][2] = '0';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end NOT if statements
			
			
			else if(strstr(instr[i], "JMP") != NULL) {
			//Proceeds if the passed in line had a jump command
				
			
				machInstr[i][0] = '1';
				machInstr[i][1] = '0';
				machInstr[i][2] = '0';
				machInstr[i][3] = '1';
				//Creates the opcode portion of the machine instruction
				
				
				jumpPass(i);
				//Creates the rest of the machine instruction
				
			}//end JMP if statements
			
			
			else if(strstr(instr[i], "JEQ") != NULL) {
			//Proceeds if the passed in line had a jump equal to command
				
			
				machInstr[i][0] = '1';
				machInstr[i][1] = '0';
				machInstr[i][2] = '1';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				jumpPass(i);
				//Creates the rest of the machine instruction
				
			}//end JEQ if statements
			
			
			else if(strstr(instr[i], "JGT") != NULL) {
			//Proceeds if the passed in line had a jump greater than command
				
			
				machInstr[i][0] = '1';
				machInstr[i][1] = '0';
				machInstr[i][2] = '1';
				machInstr[i][3] = '1';
				//Creates the opcode portion of the machine instruction
				
				
				jumpPass(i);
				//Creates the rest of the machine instruction
				
			}//end JGT if statements
			
			
			else if(strstr(instr[i], "JLT") != NULL) {
			//Proceeds if the passed in line had a jump less than command
				
			
				machInstr[i][0] = '1';
				machInstr[i][1] = '1';
				machInstr[i][2] = '0';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				jumpPass(i);
				//Creates the rest of the machine instruction
				
			}//end JLT if statements
			
			
			else if(strstr(instr[i], "CMP") != NULL) {
			//Proceeds if the passed in line had a compare command
				
			
				machInstr[i][0] = '1';
				machInstr[i][1] = '1';
				machInstr[i][2] = '0';
				machInstr[i][3] = '1';
				//Creates the opcode portion of the machine instruction
				
				
				pass(i);
				//Creates the rest of the machine instruction
				
			}//end CMP if statements
			
			
			else if(strstr(instr[i], "CLR") != NULL) {
			//Proceeds if the passed in line had a clear command
				
			
				machInstr[i][0] = '1';
				machInstr[i][1] = '1';
				machInstr[i][2] = '1';
				machInstr[i][3] = '0';
				//Creates the opcode portion of the machine instruction
				
				
				for(j = 4; j < 16; j++){
			
			
					machInstr[i][j] = '0';

					
				}
				//Creates the rest of the machine code instruction
				
				
			}//end CLR if statements
			
			
			else if(strstr(instr[i], "HLT") != NULL) {
			//Proceeds if the passed in line had a halt command
			;	
			
			
				for(j = 0; j < 4; j++){
			
			
					machInstr[i][j] = '1';

					
				}
				//Creates the opcode portion of the machine instruction
				
				for(j = 4; j < 16; j++){
			
			
					machInstr[i][j] = '0';

					
				}
				//Creates the rest of the machine code instruction
				
			}//end HLT if statements
			
			
			
			else if(strstr(instr[i], ".nd") != NULL){
			//Proceeds if the passed in instruction is the end command
				
				
				i = 51;
				//Sets i to 51 which will stop the loop from running
				
			}
			
			
			else if(strstr(instr[i], ".dw") != NULL){
			//Proceeds if the value is a declaration statement
				


			}//end .dw if statement
			
			else if(strstr(".st", instr[i]) == NULL) {
			//Proceeds if the instructions is an undefined instruction
			
				for(j = 0; j < 50; j++){
					
					if(j < 16){
					//Will only add to machine code up to 16
	
						machInstr[i][j] = '?';
						//Creates machine code instruction; all ? to signal unknown instruction
					
					}
					
					unknownInstr[i][j] = instr[i][j];
				
				}//end for loop
				
				
				unknownIndex[unknownCount] = i;
				//Stores the index of the unknown instruction
				
				unknownCount++;
				//Increments count to show another unknown instruction was added to this array
				
			}
			
			
			if(strcmp(machInstr[i], "\0"))
			//Proceeds if the machine code is not blank

				fprintf(outputFile,"%s\n", machInstr[i]);
				//Writes to the output file the completed machine code instruction along with seperation lines	

	}
	}
		i++;
				
	
	}//end second pass while loop


	for(j = 0; j < 50; j++){
		
		if(machInstr[j][8] != 'M'){
		//Proceeds if a repeat definiton has not already built the machine code
		
			if(variables[j].boolean == 1){
			//Will only print the machine code for objects with defined values
			
				printf("VARIABLE NUMBER %i", variables[j].num);
				itoa(variables[j].num, binNum, 2);
				
				for(k = 15; k >= 0; k--){
				//Creates the machine code for the data values
	 
				
					if(binNum[k] == '1')
						fprintf(outputFile,"1");
						
					else
						fprintf(outputFile,"0");
				
					
				}//end for loop
			
				
				fprintf(outputFile,"\n");
				
				
			}
		
		}
		
	}//end for loop

	fprintf(outputFile,"*\n");
	//Prints a line to seperate output
	
	
	for(j = 0; j < memCount; j++){
		
		fprintf(outputFile,"%i ", memoryAddress[j]);
		
	}
	
	//Prints out the indexs of of the instructions with memory addresses

	

	fclose(outputFile);
	//Closes the output file
	
	
	printf("Symbol Table: \n");	
	
	printf("SYMBOL\tLOCATION\n");	
	
	for(j = 0; j < 50; j++) {
		
		if(variables[j].label != NULL && variables[j].label[0] != ' ')
		
		printf("%s\t%i (0x%0i)\n",variables[j].label, variables[j].index,variables[j].index);
	}
	//Prints out the symbol table with labels and locations
	
	
	
	printf("\nUndefined Table:\n");	
	
	printf("SYMBOL\tLOCATION\n");
	
	
	for(j = 0; j < unknownCount; j++) {
				
		printf("%s\t%i (0x%0i)\n",unknownInstr[j], unknownIndex[j]);
			
	}
	//Prints out the undefined table with labels and locations
	
	
	
	
	printf("\nMultiple Table:\n");	
	
	printf("SYMBOL\tLOCATION\n");
	
	
	for(j = 0; j < multiCount; j++) {
				
		printf("%s\t%i (0x%0i)\n",multiInstr[j], multiIndex[j]);
			
	}
	//Prints out the multiple table with labels and locations
	
	
	printf("\nInstruction offsets with memory addresses: \n");
	
	
	for(j = 0; j < memCount; j++){
		
		printf("%i ", memoryAddress[j]);
		
	}
	//Prints out the indexs of of the instructions with memory addresses
	
	

	fclose(inputFile);
	
	
	return 0;
	

}//end main



void pass(int passedIn){
	

	int i = passedIn;
	//Takes the counter from the loop that was passed in and stores it in i
	
	
	int j = 0;
	//Holds the counter for various loops
	
	
	int k = 0;
	//Holds the indexes for various arrays
	
	
	int sizeOf = -1;
	//Holds the number of bits set in the operand
	
	
	int num = 0;
	//Holds the numerical value of the operand
	
	
	char operand [10];
	//Holds the operand portion of the instruction
					
					
	char binNum [10];
	//Holds the converted binary number
	
	
	char label [10];
	//Creates a char array to hold the passed in label of the variable
	
	
	char check [2];
	//Used to hold the numeric part of the label
	
	
	
	if(strstr(instr[i], "I") != NULL){
	//Checks to see if the instruction is to be immediate
	
		machInstr[i][4] = '1';
		//Creates the address mode of the machine instruction
	
	}
	
	
	else {
	//This means the instruction is direct
	
		machInstr[i][4] = '0';
		//Creates the address mode of the machine instruction
		
		
	}
	
	
	if(instr [i][13] == '0' || instr[i][13] == 'A' || instr[i][13] == ' ') {
	//Proceeds if the special register is being accessed
		
		
		machInstr[i][5] = '0';
		machInstr[i][6] = '0';
		machInstr[i][7] = '0';
		//Creates the register portion of the machine instruction
		
		
	}
	
	
	else if(instr [i][13] == '1'){
	//Proceeds if the first register is being accessed
		
		
		machInstr[i][5] = '0';
		machInstr[i][6] = '0';
		machInstr[i][7] = '1';
		//Creates the register portion of the machine instruction
		
		
	}
	
	
	else if(instr [i][13] == '2'){
	//Proceeds if the second register is being accessed
		
		
		machInstr[i][5] = '0';
		machInstr[i][6] = '1';
		machInstr[i][7] = '0';
		//Creates the register portion of the machine instruction
		
		
	}
	
	
	else if(instr [i][13] == '3'){
	//Proceeds if the third register is being accessed
		
		
		machInstr[i][5] = '0';
		machInstr[i][6] = '1';
		machInstr[i][7] = '1';
		//Creates the register portion of the machine instruction
		
		
	}
	
	
	else {
		
		
		machInstr[i][5] = '?';
		machInstr[i][6] = '?';
		machInstr[i][7] = '?';
		//If the register given was not 0,1,2,or 3, then question marks are loaded
		
		
	}
	
	
	if(strstr(instr[i], "#") != NULL){
	//Proceeds if the instruction has a signed integer
	
	
		j = 16;
		//Sets j to the max size of the operand
		
		
		k = 16;
		//Sets k to the max size of the operand
		

	
		while(instr[i][j] != '\n' && instr[i][j] != ' '&& j < 23){
			
			
			operand[(16 - k)] = instr[i][j];
			//loads the array with the operand
		
			
			j++;
			//increments j to point to the next charater in the operand
			
			k--;
			//decrements k to find the index of the next spot in operand
			
		
		}//end while loop	
		
		
		num = atoi(operand);
		//Converts the operand into a decimal number
		

		
		itoa(num,binNum,2);
		//Converts the operand into a binary number and then into a string
		
		
		sizeOf = -1;
	
		
		for(j = 0; j < 8; j++){
			
			
			if(binNum[j] == '1' || binNum[j] == '0'){
			//Proceeds if there is a bit at the index of j in bitNum
			
				sizeOf = sizeOf + 1;			
				
				
			}
		}
		
		
		if(sizeOf != 2)
		
			k = sizeOf;
			//Sets k to the number of bits in bitNum
			
			
		else
		
			k = 1;
			//Error with bitNum of 11, if statements works around that
		
		
		for(j = 15; j >= 8; j--){			
		//Creates the data Data portion of the machine instruction	
			
			
			if(binNum [k] == '1')
			
			
				machInstr[i] [j] = binNum [k];
			
			
			else
			
				machInstr[i] [j] = '0';
			
			
			k--;
			
		}

		
		for(j = 0; j < 16; j++){

			
			operand[j] = ' ';
			//Clears the operand for the next use
			
			
		}
		

		j = 0;
		k = 0;
		//Sets j and k back to 0 for later use
		
	}//end constant digit assignment if statement
	
	
	else if(strstr(instr[i], "M") != NULL){
		
		
		memoryAddress[memCount] = i;
		//Loads the index of the current instruction into the array
		
		
		memCount++;
		//Increments memCount as another index has been loaded into the array
		
		
		j = 15;
		//Sets j to the max size of the operand
	
	
		k = 15;
		//Sets k to the max size of the operand					

	
		while(instr[i][j] != '\n' && instr[i][j] != ' '&& j < 23){
			
			
			label[(15 - k)] = instr[i][j];
			//loads the label into the array
								
			
			j++;
			//increments j to the index of the next character in the instruction
			
			
			k--;
			//decrements k to find the index of the next spot in label
			
		
		}//end while loop
		
		
		
		
		for(j = 0; j < 50; j++){
			
			
			if(strcmp(label, variables[j].label) == 0){
			//Compares the label from the instruction to one in the structure
			
										
				k = j;
				//Sets k to the index of the matching label
				
				j = 51;
				//Increases j in order to fall out of the loop	
			
			}
		}//end for loop
		
		
		
		if(strstr(instr[i], "I") != NULL){
		
			
			itoa(variables[k].num,binNum,2);
			//Converts the operand into a binary number and then into a string
			
		
			sizeOf = -1;
			
			
			for(j = 0; j < 8; j++){
				
				
				if(binNum[j] == '1' || binNum[j] == '0'){
				//Proceeds if there is a bit at the index of j in bitNum
												
					
					sizeOf = sizeOf + 1;
					
					
				}
			}
			
			
			k = sizeOf;
			//Sets k to the number of bits in bitNum
			
			
			for(j = 15; j >= 8; j--){
			//Creates the data portion of the machine code									
				
				
				if(binNum [k] == '1')
				
				
					machInstr[i] [j] = binNum [k];
				
				
				else
				
					machInstr[i] [j] = '0';
					//Creates the data Data portion of the machine instruction
				
				k--;
				
			}
		
		}
		
		else{
			
							
			check [0] = label[1];
			check [1] = label[2];
			//Sets check to the numeric part of the label
			
			num = atoi(check);
			//Converts the label into a decimal number
			
			
			
			itoa(num, binNum, 2);
			//Converts the label into a binary number and then into a string
		
			
			
			sizeOf = -1;
		
			for(j = 0; j < 8; j++){
				
				
				if(binNum[j] == '1' || binNum[j] == '0'){
				//Proceeds if there is a bit at the index of j in bitNum

					sizeOf = sizeOf + 1;
					
				}
			}
			

			k = sizeOf;
			//Sets k to the number of bits in bitNum
			
			
			for(j = 15; j >= 8; j--){
			//Creates the data Data portion of the machine instruction			
				
				
				if(binNum [k] == '1')
				
					machInstr[i] [j] = binNum [k];
				
				else
				
					machInstr[i] [j] = '0';
					
				
				k--;
				
			}
			
			
			check [0] = ' ';
			check [1] = ' ';
			//Clears check for later use
			
		}
		
		for(j = 0; j < 3; j++){

			
			label[j] = ' ';
			//Clears label for the next use
			
			
		}
		
		j = 0;
		k = 0;
		//Sets j and k to zero for later use
		
		
	}//end variable assignment if statement
	
	
	else if(machInstr[i][j] != ' ') {
	//Proceeds if the operand is unknown
	
	
		for(j = 0; j < 50; j++){
		
			unknownInstr[unknownCount][j] = machInstr[i][j];
			//Loads the unknown instruction into the unknown array
		
		}
		
		
		unknownIndex[unknownCount] = i;
	    //Stores the index of the unknown instruction
		
		unknownCount++;
		//Increments unknownCount to show another unkown instruction has been passed in		

		for(j = 8; j < 16; j++) {
			
			machInstr[i][j] = 'U';
			//Sets U values to the machine code instruction
			
		}
	}
	
	
	
	j= 0; 
	//Sets j to zero for later use
	
}


void jumpPass(int passedIn){
	
	
	int i = passedIn;
	//Takes the counter from the loop that was passed in and stores it in i
	
	int j = 15;
	//Holds the counter for various loops
	
	
	int k = 15;
	//Holds the indexs for various arrays
	
	
	int num = 0;
	//Holds the index of the labeled instruction
	
	
	int sizeOf = -1;
	//Holds the number of bits in a binary number
	
	
	char label [10];
	//Holds the label of the instruction
	
	char binNum [10];
	//Holds the converted binary 
	
	
	memoryAddress[memCount] = i;
	//Loads the index of the current instruction into the array
	
	
	memCount++;
	//Increments memCount as another index has been loaded into the array

	
	while(instr[i][j] != '\n' && instr[i][j] != ' '&& j < 23){
		
		
		label[(15 - k)] = instr[i][j];
		//loads the label into the array
							
		
		j++;
		//increments j to the index of the next character in the instruction
		
		
		k--;
		//decrements k to find the index of the next spot in label
		
	
	}//end while loop
	
	
  	for(j = 0; j < 50; j++){
			
			
		if(strcmp(label, variables[j].label) == 0){
		//Compares the label from the instruction to one in the structure
		
			num = variables[j].index;
			//Assigns the index of the labled instructions to num
			
			j = 51;
			//Sets j to 51 causing the loop to stop
			

		}
		
	}//end for loop
	

	machInstr[i][4] = '0';
	machInstr[i][5] = '0';
	machInstr[i][6] = '0';
	machInstr[i][7] = '0';
	//Creates the register and address portion of the machine instruction
	
	
	itoa(num, binNum, 2);
	//Converts the label into a binary number and then into a string
		
	
			
	for(j = 0; j < 8; j++){
		
		
		if(binNum[j] == '1' || binNum[j] == '0'){
		//Proceeds if there is a bit at the index of j in bitNum

			sizeOf = sizeOf + 1;
			
		}
	}
	

	k = sizeOf;
	//Sets k to the number of bits in bitNum

	
	for(j = 15; j >= 8; j--){
	//Creates the data Data portion of the machine instruction			
		
		
		if(binNum [k] == '1'){		
		
			machInstr[i][j] = binNum [k];
			
		
	}
		else
		
			machInstr[i][j] = '0';
			
		
		k--;
		
	}
	
}//end jumpPass



char* itoa(int num, char* str, int base){
	
	
	int i = 0;
	
	
	int boolean = 0;
	
	
	if(num == 0){
	//Proceeds if the number passed in is just 0
	
		i=i+1;
		
		str[i] = '0';
		
		str[i] = '\0';
		//Adds a null terminator to the number
		
		return str;
		
		
	}
	
	
	
    if (num < 0 && base == 10) {
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.	
    	
    	
        boolean = 1;
        
        
        num = -num;
        
        
    }
 

    while (num != 0)  {
     // Processes individual digits and creates the number
     
        int rem = num % base;
        
        
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        
        
        num = num/base;
        
    }
 
   
    if (boolean == 1)
    // If number is negative, append '-'
    
    
        str[i++] = '-';
        
 
    str[i] = '\0'; 
	// Append string terminator
    
 

    reverse_string(str);
    // Reverse the string
 
    return str;
}


char* reverse_string(char *str) {
	
	
char temp;
//Holds the char being moved


int len = strlen(str) - 1;
//Holds the size of the inputued string


int i;
//Holds the counter for the loop


int k = len-1;
//Also holds the length of the string, but is used find the half way point


for(i = 0; i < len; i++){
//Will go through the string and reverse the string
	
	
	temp = str[k];
	
	str[k] = str[i];
	
	str[i] = temp;
	
	k--;

	  
    if(k == (len / 2)){    
    /* As 2 characters are changing place for each cycle of the loop
       only traverse half the array of characters and then break */
       
		   
   	    break;
   	    
    }
    
    }//end for loop
    
}

 


