/*
Names: Jace Archer
Class: CSC 214.001
Project 1 C: Relocating Loader
April 29th, 2016


Files Used: File read in from command Line, and proj1c.out for output

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//libraries


#define WORD_LENGTH 16
#define HALF_INSTRUCTION 8
#define MAX_WORDS 256
#define WORD_LENGTH 16
#define COUNT_LENGTH 8
#define FLAG_LENGTH 3
#define OP_LENGTH 4
#define REG_LENGTH 3
#define ADDRESS_LENGTH 1
#define LOCATION_LENGTH 8

int convertInstr(char[WORD_LENGTH], int); 
// converts an instruction into decimal value


void fetch(); 
//gets instructions from the main memory after it has been offset


void decode(); 
//decodes instructions


void execute(); 
//executes instructions


void dump(); 
//displays all of the data 


int convertInstr(char[WORD_LENGTH], int); 
//converts an instruction into decimal value


void setValue(); 
//converts a binary value to decimal value


void setFlag(); 
//Sets condition code


void makeBinaryNum(int, int); 
//Converts an integer into a binary String and assigns it to newBin


void printBinaryNum(int, int); 
//Converts an integer into a binary String and prints it out


int powOfTwo(int);
//Will return the value of two raised to the passed in exponent


struct machine {
//Creates a structure that will hold the machine's data


	
    int r0; 
	//special register
	
	
    int r1; 
	//register one
	
	
    int r2; 
	//register two
	
	
    int r3; 
	//register three
	
	
    char flag[FLAG_LENGTH + 1]; 
	//character array that will hold the binary representaion of the condition flag
	
	
	char instructionRegister[WORD_LENGTH + 1];
	//character array that will hold the binary representation of the instructions in the IR
	
	
    long memory[MAX_WORDS]; 
	//array that will hold the data in main memory
	

};//end machine structure



struct machine data; 
//Creates an instance of the machine structure


char instr[50][18]; 
//The character array that will hold the binary representation of the passed in instructions


int progCount = 0; 
//Creates a program counter that will show the number of instructions proccessed


int errorFlag = 0;
//Creates a variable that will show whether or not an error has occured in the program


int numInstruc = 0;
//Creates instruction counter that will show the number of instructions read in


	
int sizeOfOffset = 0;
//Holds the size of the offset given by the user

char opCode[OP_LENGTH + 1]; 
//the char array that holds the operation code, that will determine which command is executed


char addressCode[ADDRESS_LENGTH + 1]; 
//char array that hold the address code which will say whether a command is direct or immediate


char regCode[REG_LENGTH + 1]; 
//char array that holds the register code which will tell which register is being used/modifyied


char location[LOCATION_LENGTH + 1]; 
/*char array that hold either the binary location of where an operation is being performed or the 
  data will be used in the operation
*/


int locationNum;
//the decimal representaion of location


char newBin [8];
//Holds the converted binary number being built




int main(int argc, char *argv[]) {

	
	FILE *inputFile;
	//The file object that will hold the file where instructions are to be read in from
	
	
	char *inputFileName = argv[2];
	//Holds the name for the input file that is given by user
	
	
	inputFile = fopen(inputFileName, "r");
	//Gives the program a way to access the input file and gives it permission to read it
	
	
	int i = 0;
	//Holds the index for various arrays and loops
	

	int locationConvert = 0;
	//Holds the integer value of the location portion of the data
	
	
	int j = 0;
	//Holds the counter for various loops
	
	
	int offsetHolder;
	//Will hold sizeOfOffset, and will be incremented during the first print out
	
	
	int numOffsets = 0;
	//Holds the number of offsets that the input gives
	
	
	int size = 0;
	//Holds the number of lines read in from the file
	
	
	int offsets[60];
	//Holds the array of indexs of spots in memory locations
	
	
	char temp[30];
	//Holds the line of offsets from the file
	
	
	char location[8];
	//Stores the location or data portion of the instruction
	
	
	char instruc[8];
	//Stores the register, address mode, and command portions of the instruction
	
	
	char convertedInstruct [15];
	//Holds the completed instruction that has been offset
	
	
	char *data;
	//Holds the individual offset from the file
	
	
	sizeOfOffset = strtol(argv[1], NULL, 16);
	//Sets sizeOfOffset the the decimal value of the number passed in from the user
	
	
	while(strstr(fgets(instr[i], WORD_LENGTH + 2, inputFile), "*") == NULL){	
	//Loads the instructions from the file into memory until a star is reached
		
		
		i++;
		//Increments i to point to the next index
		
		
		size++;
		//Increments size to show another instruction has been read in
		
		
		if (numInstruc >= MAX_WORDS) {
				
			
			fprintf(stderr, "Error: Maximum number of instructions has been reached.");
			exit(1);
			//Prints out an error message and exits the program if the prorgam has read in too many instructions
			
		
		} // end if
			
			
		else if (sizeof(instr[numInstruc]) > WORD_LENGTH + 2) {
				
		
			fprintf(stderr, "Error: Bit overflow!");
			exit(1);
			//Prints out an error message and exits the program if the instruction has too many characters
			
			
			} // end if
			
			
		else if((sizeof(instr[numInstruc]) < WORD_LENGTH  + 2)){
			
			
			fprintf(stderr, "Error: Bit underflow!");
			exit(1);
			//Prints out an error message and exits the program if the instruction has too few characters
			
			
		}
		
		
		numInstruc++;
		//Increments numInstruc to show another instruction has been read in
	
			
		
	}//end while
	
	
	
	fgets(temp, 30, inputFile);
	//Loads the last line of the file into temp
	
	
	
	data = strtok(temp, " ") ;
	//Splits the temp string by spaces and loads it into data
	
	
	i = 0;
	//Resets i for later use
	
	
	
	while(data != NULL){
	//Will run until data is a null value
	
			
		offsets[i] = atoi(data);
		//Converts data into an integer and loads it into the offset array
			
		
		data = strtok(NULL, " ");
		//Loads the next offset into data
		
		
		i++;
		//Increments i to point to the next index of offset
		
		
		numOffsets++;
		//Increments numOffsets indicating another offset has been read in
		
		
		
	}//end while loop
	
	
	
	i = 0;
	//Resets i for later use
	
	
	
	while(i < numOffsets){
		
	
		
		j = 0;
		//Sets j back to zero to restart iteration
		
	
		while(j < 2){
		//Will Run through twice to get both parts of the instruction. Implementation without loop caused error
			
			
			if(j == 0){
			//Proceeds if the loop is on its first iteration
				
				
				strncpy(instruc, instr[offsets[i]], HALF_INSTRUCTION);
				//Will copy the instruction portion of the instruction into instruc
				
				
				instruc[8] = '\0';
				//Adds a null terminator at the end of instruc
							
				
			}//end if
			
			
			else{
				
			
				strncpy(location, instr[offsets[i]] + HALF_INSTRUCTION, HALF_INSTRUCTION);
				//Copies the data / location portion of the instruction into location
				
				
				location[8] = '\0';
				//Adds a null terminator at the end of location
	
				
			}//end else
			
			
			j++;
			//Increments j for the next iteration
			
			
		}//end outer loop
		
		
		locationConvert = convertInstr(location, 8) + sizeOfOffset;
		//Converts the location portion into an integer and then offsets it by the passed in offset
		
		
		makeBinaryNum(locationConvert, HALF_INSTRUCTION);
		//Converts the newly offsetted location into a binary String
		
		
		strcpy(location,newBin);
		//Copies the value stored into newBin to location
		
		
		location[8] = '\0';
		//Adds a null terminator at the end of location	
		
		
		strcpy(convertedInstruct, instruc);
		//Copies the instruction portion of the instruction into the the new instruction
		
		
		strcpy(convertedInstruct + 8, location);
		//Copies the offsetted location  into the the new instruction
	
		
		
		strcpy(instr[offsets[i]], convertedInstruct);
		//Loads the new instruction into memory
			
		
		i++;
		//Increments i to point to the next index of offset
		
		
	}//end while loop
	
	
	i = 0;
	//Sets i back to zero for later use
	
	
	offsetHolder = sizeOfOffset;
	
		
	printf("Adjusted: \n\n");
	
	
	printf("Location(memory-hex/bin)\tCode\n");
	//Prints out the beginning out the output
	
	
	while(i < size){
	//Will run untill all instructions have been printed out
		
		
		j = 0;
		//Sets j back to zero to point at the first character in the instruction
		
		
		printf("0x%02X  ", offsetHolder);
		//Prints out the offset memory location
		
		
		printBinaryNum(offsetHolder, 8);
		//Prints out the binary representation of the offset
		
		
		printf("\t\t\t");
		//Tabs over to the code of the instruction
		
		
		while (j < 16){
		//Will run through the entire instruction
		
		
			if(instr[i][j] != '\n'){
			//Stops the end of line character from being printed out
	
				
				printf("%c", instr[i][j]);
				//Prints out a single chracter of the instruction to the console
				
				
				j++;
				//Increments j to point at the next character in the instruction
				
				
			}//end if
			
		
		}//end while
		
		
		i++;
		//Increments i to point to the next index
		
		
		offsetHolder++;
		//Increments sizeOfOffset so that the next memory location is printed out
	
	
		printf("\n");
		//Creates a new line to seperate output
		
	
		
	}//end while loop


	fetch();
	
	printf("AFTER FETCH\n");

	return 0;
 	

}//end main


void fetch() { 
//gets instructions from input file provided by the user

	int i = 0;


	while (i < numInstruc) { 
	//gets the instructions from the file, adds + 2 to the size to account for \0 and \n from each line
	

		data.memory[i] = convertInstr(instr[i], WORD_LENGTH);
		//loads the instruction into the main memory array after converting it to a decimal
		
		
		i++;
		
	
	} // end while
	

	instr[numInstruc][0] = '\0'; 
	//sets a null character to provide a way to stop the code from accessing the 2nd deminsion of the array 	

	
	i = 0;
	//Sets i back to 0 for later use
	
	
	while (i <= numInstruc) {
	//Will at least run a number of times equal to the number of instruction read in
		
	
		strncpy(data.instructionRegister, instr[progCount], WORD_LENGTH);
		//Loads the current instruction into the IR to be processed 
		
		
		if(errorFlag == 0){
		//Will continue if an error has not occurred
			
		    decode(); 
		    //decodes the machine instruction and splits it up into readable parts

		
		    if(errorFlag == 0){
		    //Will continue if an error has not occurred
		
		
			    execute();
			    //Will execute the newly decoded instruction

		    
		    }
				
		
		    else{
			
			 
			    dump();
			    //Prints out the contents that are currently stored in memory
			
			
			    exit(1);
			    //exits the program
			
			
		    }
		
		
			progCount++;
			//Increments progCount meaning another instruction has been completed
			
			
		}
		
		
		else{
			
			
			dump();
			//Prints out the contents that are currently stored in memory
			
			
			exit(1);
			//exits the program
			
			
		}
		
		
		i++;
		
			
	} // end while
	
	
	printf("ERROR NO HALT COMMAND WAS READ IN, NOW PERFORMING PRINT OUT OF CURRENT DATA\n");
	
	
	dump();
	//Prints an error message and performs a final dump if no halt command was read in
	

} // end fetch


void decode(){

	
	strncpy(opCode, data.instructionRegister, OP_LENGTH);
	//Copies the first 4 bits of the IR into the opcode
	
	
	strncpy(addressCode, data.instructionRegister + OP_LENGTH, ADDRESS_LENGTH);
	//Copies the 5th bit of the IR into the addressCode 
	
	
	strncpy(regCode, data.instructionRegister + OP_LENGTH + ADDRESS_LENGTH, REG_LENGTH); 
	//Copies the 6th through 8th bits of the IR into the regCode as the register code
	
	
	if(strcmp(regCode, "000") != 0 && strcmp(regCode, "001") != 0 && strcmp(regCode, "010") != 0
	   && strcmp(regCode, "011") != 0) {
    //Checks to see if a valid register was given by the instruction	
		
		
		errorFlag = 1;
		//Sets the error flag to 1, meaning the program will not execute further
		
		
	}
	
	
	strncpy(location, data.instructionRegister + OP_LENGTH + ADDRESS_LENGTH + REG_LENGTH, LOCATION_LENGTH); 
	//Copies the last 8 bits of the IR into location as the data or location meant to be read
	
	
	locationNum = convertInstr(location,LOCATION_LENGTH);
	//Converts the location or data into a decimal number and stores it in locationNum
	
	
}//end decode

void execute(){


	if((strcmp(opCode,"1111")) == 0) {
	//Halt command

		
		dump();
		//prints out all the data
		
		
		exit(0);
		//exits the program 
		
	
	}
	
	else if((strcmp(opCode,"0000")) == 0) {
	//Load command
	
		
		if((strcmp(addressCode,"0")) == 0)	{
		//Direct 
		
			
			if((strcmp(regCode, "000") == 0)) {
			//Direct Load into register 0
			
			
			 data.r0 = data.memory[locationNum];
			 //loads the value at the given loaction in memory to r0
			 
			 
			 setFlag(data.r0);
			 //Sets the flag condition based on the value in r0
			 
			
			}
			
			
			else if((strcmp(regCode, "001") == 0)) {
			//Direct Load into register 1
			
			
			 data.r1 = data.memory[locationNum];
			 //loads the value at the given location in memory to r1
			 
			 
			 setFlag(data.r1);
			 //Sets the flag condition based on the value in r1
			 
			
			}
			
			
			else if((strcmp(regCode, "010") == 0)) {
			//Direct Load into register 2
			
			
			 data.r2 = data.memory[locationNum];
			 //loads the value at the given location in memory to r2
			 
			 
			 setFlag(data.r2);
			 //Sets the flag condition based on the value in r2
			 
			
			}
			
			
			else if((strcmp(regCode, "011") == 0)) {
			//Directly Load into register 3
			
			
			 data.r3 = data.memory[locationNum];
			 //loads the value at the given lacation in memory to r3
			 
			 
			 setFlag(data.r3);
			 //Sets the flag condition based on the value in r3
			 
			 		 
			}
			
			
		}//end Direct Load if statements
		
		
		else if (strcmp(addressCode, "1") == 0) {
		//Immediate Load
		
		
			if (strcmp(regCode, "000") == 0){
			//Immidiate Load into register 0
			
			
				data.r0 = locationNum;
				//loads the value of the data from the instruction into r0
				
				
				setFlag(data.r0);
				//sets flag based on the data passed from the instruction
				
				
			}
			
			
			else if (strcmp(regCode, "001") == 0){
			//Immediate Load into register 1
			
			
				data.r1 = locationNum;
				//loads the value of the data from the instruction into r2
				
				
				setFlag(data.r1);
				//sets flag based on the data passed from the instruction
				
				
			}
			
			
			else if(strcmp(regCode,"010") == 0) {
			//Immediate Load into register 2
			
			
				data.r2 = locationNum;
				//loads the value of the data from the instruction into r2
				
				
				setFlag(data.r2);
				//sets flag based on the data passed from the instruction
				
				
			}
			
			
			else if(strcmp(regCode,"011") == 0) {
			//Immediate Load into register 3
			
			
				data.r3 = locationNum;
				//loads the value of the data from the instruction into r3
				
				
				setFlag(data.r3);
				//sets flag based on the data passed from the instruction
				
				
			}
			
		
		}//end Immediate Load if statementss		
		
	}//end Load if statements
	
	
	else if(strcmp(opCode, "0001") == 0){
	//Store Command
	
	
		if(strcmp(addressCode, "0") == 0){
		//Direct Store
		
			
			if(strcmp(regCode, "000") == 0){
			//Direct Store of register 0
				
				
				data.memory[locationNum] = data.r0;
				//loads the value of r0 into memory at the given location 
				

                setFlag(data.r0);
                //sets flag based on r0
                
			}
			
			
			else if(strcmp(regCode, "001") == 0){
			//Direct Store of register 1
				
				
				data.memory[locationNum] = data.r1;
				//loads the value of r1 into memory at the given location 
				
				
                setFlag(data.r1);
                //sets flag based on r1
                
                
			}
			
			
			else if(strcmp(regCode, "010") == 0){
			//Direct Store of register 2
				
				
				data.memory[locationNum] = data.r2;
				//loads the value of r2 into memory at the given location
				 
				
                setFlag(data.r2);
                //sets flag based on r2
                
                
			}
			
			
			else if(strcmp(regCode, "011") == 0){
			//Direct Store of register 3
				
				
				data.memory[locationNum] = data.r3;
				//loads the value of r3 into memory at the given location 
				
				
                setFlag(data.r3);
                //sets flag based on r3
                
                
			}
			
		}//end Direct Store if statements
		
		
		else if((strcmp(addressCode, "1") == 0)) {
		//Immediate Store
			
			
			if(strcmp(regCode, "000") == 0) {
			//Immediate Store of register 0
			
			
				data.memory[data.r0] = data.r0;
				//loads the value of r0 into memory at the location of r0
				
				
                setFlag(data.r0);
                //sets the flag based on r0
                
                
			}
			
			
			else if(strcmp(regCode, "001") == 0) {
			//Immediate Store of register 1
			
			
				data.memory[data.r1] = data.r1;
				//loads the value of r1 into memory at the location of r1
				
				
                setFlag(data.r1);
                //sets the flag based on r1
                
                
			}
			
			
			else if(strcmp(regCode, "010") == 0) {
			//Immediate Store of register 2
			
			
				data.memory[data.r2] = data.r2;
				//loads the value of r2 into memory at the location of r2
				
				
                setFlag(data.r2);
                //sets the flag based on r2
                
                
			}
			
			
			else if(strcmp(regCode, "011") == 0) {
			//Immediate Store of register 3
			
			
				data.memory[data.r3] = data.r3;
				//loads the value of r3 into memory at the location of r3
				
				
                setFlag(data.r3);
                //sets the flag based on r3
                
			}
			
			
		}//end Immediate Stoe if statements
	
	}//end Store if statements
	
	
	else if (strcmp(opCode, "0010") == 0){
	//Add Command on Special register
	
	
		if (strcmp(addressCode, "0") == 0)	{
		//Direct Add on Special register
		
			
			data.r0 = data.r0 + data.memory[locationNum];
			//Adds the value in memory at the given location to r0
			
			
			setFlag(data.r0);
			//Sets the flag based on the new value of r0
			
			
		}//end Direct Add if statement
		
		
		else if (strcmp(addressCode, "1") == 0)	{
		//Immediate Add on Special register
		
		
			data.r0 = data.r0 + locationNum;
			//Adds the value given by the instruction to r0
			
			
			setFlag(data.r0);
			//Sets the flag based on the new value of r0
			
			
		}//end Immediate Add If statement
		
	}//end Add if statements
	
	
	else if (strcmp(opCode, "0011") == 0){
	//Subtract Command on Special register
	
		if (strcmp(addressCode, "0") == 0)	{
		//Direct Subtract on Special register
		
			
			data.r0 = data.r0 - data.memory[locationNum];
			//Subtracts the value in memory at the given location to r0
			
			
			setFlag(data.r0);
			//Sets the flag based on the new value of r0
			
			
		}//end Direct Add if statement
		
		
		else if (strcmp(addressCode, "1") == 0)	{
		//Immediate Substract on Special register
		
		
			data.r0 = data.r0 - locationNum;
			//Subtracts the value given by the instruction to r0
			
			
			setFlag(data.r0);
			//Sets the flag based on the new value of r0
			
			
		}//end Immediate Subtract If statement
		
	}//end Subtract if statements
	
	
	else if (strcmp(opCode, "0100") == 0){
	//Add Command on a given register
		
	
		if (strcmp(addressCode, "0") == 0)	{
		//Direct Add on a given register
		
		
			if(strcmp(regCode,"000") == 0){
			//Direct Add on register 0
			
			
				data.r0 = data.r0 + data.memory[locationNum];
				//Adds the value in memory at the given location to r0
				
				
				setFlag(data.r0);
				//Sets the flag based on the new value of r0
			
			
			}
			
			
			else if(strcmp(regCode,"001") == 0){
			//Direct Add on register 1
			
			
				data.r1 = data.r1 + data.memory[locationNum];
				//Adds the value in memory at the given location to r1
				
				
				setFlag(data.r1);
				//Sets the flag based on the new value of r1
			
			
			}
			
			
			else if(strcmp(regCode,"010") == 0){
			//Direct Add on register 2
			
			
				data.r2 = data.r2 + data.memory[locationNum];
				//Adds the value in memory at the given location to r2
				
				
				setFlag(data.r2);
				//Sets the flag based on the new value of r2
			
			
			}
			
			
			else if(strcmp(regCode,"011") == 0){
			//Direct Add on register 3
			
			
				data.r3 = data.r3 + data.memory[locationNum];
				//Adds the value in memory at the given location to r3
				
				
				setFlag(data.r3);
				//Sets the flag based on the new value of r3
				
			
			}
			
		}//end Direct ADR if statements
		
		
		else if (strcmp(addressCode, "1") == 0)	{
		//Immediate Add on a given register
		
		
			if(strcmp(regCode,"000") == 0){
			//Immediate Add on register 0
			
		
				data.r0 = data.r0 + locationNum;
				//Adds the value given by the instruction to r0
				
				
				setFlag(data.r0);
				//Sets the flag based on the new value of r0
				
				
			}
			
			
			else if(strcmp(regCode,"001") == 0){
			//Immediate Add on register 1
			
		
				data.r1 = data.r1 + locationNum;
				//Adds the value given by the instruction to r1
				
				
				setFlag(data.r1);
				//Sets the flag based on the new value of r1
				
				
			}
			
			
			else if(strcmp(regCode,"010") == 0){
			//Immediate Add on register 2
			
		
				data.r2 = data.r2 + locationNum;
				//Adds the value given by the instruction to r2
				
				
				setFlag(data.r2);
				//Sets the flag based on the new value of r2
				
				
			}
			
			
			else if(strcmp(regCode,"011") == 0){
			//Immediate Add on register 3
			
		
				data.r3 = data.r3 + locationNum;
				//Adds the value given by the instruction to r3
				
				
				setFlag(data.r3);
				//Sets the flag based on the new value of r3
				
				
			}
			
			
		}//end Immediate ADR If statements
		
		
	}//end ADR if statements	
	
	else if (strcmp(opCode, "0101") == 0){
	//Subtract Command on a given register
		
	
		if (strcmp(addressCode, "0") == 0)	{
		//Direct Subtract on a given register
		
		
			if(strcmp(regCode,"000") == 0){
			//Direct Subtract on register 0
			
			
				data.r0 = data.r0 - data.memory[locationNum];
				//Subtracts the value in memory at the given location from r0
				
				
				setFlag(data.r0);
				//Sets the flag based on the new value of r0
			
			
			}
			
			
			else if(strcmp(regCode,"001") == 0){
			//Direct Subtract on register 1
			
			
				data.r1 = data.r1 - data.memory[locationNum];
				//Subtracts the value in memory at the given location from r1
				
				
				setFlag(data.r1);
				//Sets the flag based on the new value of r1
			
			
			}
			
			
			else if(strcmp(regCode,"010") == 0){
			//Direct Subtract on register 2
			
				data.r2 = data.r2 - data.memory[locationNum];
				//Subtracts the value in memory at the given location from r2
				
				
				setFlag(data.r2);
				//Sets the flag based on the new value of r2
			
			
			}
			
			
			else if(strcmp(regCode,"011") == 0){
			//Direct Subtract on register 3
			
				data.r3 = data.r3 - data.memory[locationNum];
				//Subtracts the value in memory at the given location from r3
				
				
				setFlag(data.r3);
				//Sets the flag based on the new value of r3
			
			
			}
			
		}//end Direct ADR if statements
		
		
		else if (strcmp(addressCode, "1") == 0)	{
		//Immediate Subtract on a given register
		
		
			if(strcmp(regCode,"000") == 0){
			//Immediate Subtract on register 0
		
		
				data.r0 = data.r0 - locationNum;
				//Subtracts the value given by the instruction from r0
				
				
				setFlag(data.r0);
				//Sets the flag based on the new value of r0
				
				
			}
			
			
			else if(strcmp(regCode,"001") == 0){
			//Immediate Subtract on register 1
		
		
				data.r1 = data.r1 - locationNum;
				//Subtracts the value given by the instruction to r1
				
				
				setFlag(data.r1);
				//Sets the flag based on the new value of r1
				
				
			}
			
			
			else if(strcmp(regCode,"010") == 0){
			//Immediate Subtract on register 2
		
		
				data.r2 = data.r2 + locationNum;
				//Subtracts the value given by the instruction from r2
				
				
				setFlag(data.r2);
				//Sets the flag based on the new value of r2
				
				
			}
			
			
			else if(strcmp(regCode,"011") == 0){
			//Immediate Subtract on register 3
		
		
				data.r3 = data.r3 - locationNum;
				//Subtracts the value given by the instruction from r3
				
				
				setFlag(data.r3);
				//Sets the flag based on the new value of r3
				
				
			}
			
			
		}//end Immediate SUR If statements
		
		
	}//end SUR if statements
	
	
	else if (strcmp(opCode, "0110") == 0){
	//AND Command
	
	
		if (strcmp(addressCode, "0") == 0){
		//Direct AND Command
		
		
			if(strcmp(regCode,"000") == 0){
			//Direct AND with register 0
			
			
				data.r0 = data.r0 & data.memory[locationNum];
				//Performs a logical AND operation with r0 and the value in memory at given location
				
				
				setFlag(data.r0);
				//Sets the flag based on the new value of r0
				
				
			}
			
			
			else if(strcmp(regCode,"001") == 0){
			//Direct AND with register 1
			
			
				data.r1 = data.r1 & data.memory[locationNum];
				//Performs a logical AND operation with r1 and the value in memory at given location
				
				
				setFlag(data.r1);
				//Sets the flag based on the new value of r1
				
				
			}
			
			
			else if(strcmp(regCode,"010") == 0){
			//Direct AND with register 2
			
			
				data.r2 = data.r2 & data.memory[locationNum];
				//Performs a logical AND operation with r2 and the value in memory at given location
				
				
				setFlag(data.r2);
				//Sets the flag based on the new value of r2
				
				
			}
			
			
			else if(strcmp(regCode,"011") == 0){
			//Direct AND with register 3
			
			
				data.r3 = data.r3 & data.memory[locationNum];
				//Performs a logical AND operation with r3 and the value in memory at given location
				
				
				setFlag(data.r3);
				//Sets the flag based on the new value of r3
				
				
			}
			
			
		}//end Direct AND if statements
		
		
		else if (strcmp(addressCode, "1") == 0){
		//Immediate AND 
		
		
			if (strcmp(regCode, "000") == 0){
			//Immediate AND with regiter 0
			
			
				data.r0 = data.r0 & locationNum;
				//Performs a logicla AND operations with r0 and the data given by the instruction
				
				
				setFlag(data.r0);
				//Sets Flag based on the new value of r0
			
			
			}
			
			
			else if (strcmp(regCode, "001") == 0){
			//Immediate AND with regiter 1
			
			
				data.r1 = data.r1 & locationNum;
				//Performs a logicla AND operations with r1 and the data given by the instruction
				
				
				setFlag(data.r1);
				//Sets Flag based on the new value of r1
			
			
			}
			
			
			else if (strcmp(regCode, "010") == 0){
			//Immediate AND with regiter 2
			
			
				data.r2 = data.r2 & locationNum;
				//Performs a logicla AND operations with r2 and the data given by the instruction
				
				
				setFlag(data.r2);
				//Sets Flag based on the new value of r2
			
			
			}
			
			
			else if (strcmp(regCode, "011") == 0){
			//Immediate AND with regiter 3
			
			
				data.r3 = data.r3 & locationNum;
				//Performs a logicla AND operations with r3 and the data given by the instruction
				
				
				setFlag(data.r3);
				//Sets Flag based on the new value of r3
			
			
			}
			
			
		}//end Immediate AND if statements
		
	}//end AND if statements
	
	
		else if (strcmp(opCode, "0111") == 0){
		//OR Command
	
	
			if (strcmp(addressCode, "0") == 0){
			//Direct OR Command
		
		
				if(strcmp(regCode,"000") == 0){
				//Direct OR with register 0
				
				
					data.r0 = data.r0 | data.memory[locationNum];
					//Performs a logical OR operation with r0 and the value in memory at given location
					
					
					setFlag(data.r0);
					//Sets the flag based on the new value of r0
					
					
				}
				
				
				else if(strcmp(regCode,"001") == 0){
				//Direct OR with register 1
				
				
					data.r1 = data.r1 | data.memory[locationNum];
					//Performs a logical OR operation with r1 and the value in memory at given location
					
					
					setFlag(data.r1);
					//Sets the flag based on the new value of r1
					
					
				}
				
				
				else if(strcmp(regCode,"010") == 0){
				//Direct OR with register 2
				
				
					data.r2 = data.r2 | data.memory[locationNum];
					//Performs a logical OR operation with r2 and the value in memory at given location
					
					
					setFlag(data.r2);
					//Sets the flag based on the new value of r2
					
					
				}
				
				
				else if(strcmp(regCode,"011") == 0){
				//Direct AND with register 3
				
				
					data.r3 = data.r3 | data.memory[locationNum];
					//Performs a logical OR operation with r3 and the value in memory at given location
					
					
					setFlag(data.r3);
					//Sets the flag based on the new value of r3
					
					
				}
				
				
			}//end Direct OR if statements
		
		
			else if (strcmp(addressCode, "1") == 0){
			//Immediate OR 
			
			
				if (strcmp(regCode, "000") == 0){
				//Immediate OR with regiter 0
				
				
					data.r0 = data.r0 | locationNum;
					//Performs a logicla OR operations with r0 and the data given by the instruction
					
					
					setFlag(data.r0);
					//Sets Flag based on the new value of r0
				
				
				}
				
				
				else if (strcmp(regCode, "001") == 0){
				//Immediate OR with regiter 1
				
				
					data.r1 = data.r1 | locationNum;
					//Performs a logicla OR operations with r1 and the data given by the instruction
					
					
					setFlag(data.r1);
					//Sets Flag based on the new value of r1
				
				
				}
				
				
				else if (strcmp(regCode, "010") == 0){
				//Immediate OR with regiter 2
				
				
					data.r2 = data.r2 | locationNum;
					//Performs a logicla OR operations with r2 and the data given by the instruction
					
					
					setFlag(data.r2);
					//Sets Flag based on the new value of r2
				
				
				}
				
				
				else if (strcmp(regCode, "011") == 0){
				//Immediate OR with regiter 3
				
				
					data.r3 = data.r3 | locationNum;
					//Performs a logicla OR operations with r3 and the data given by the instruction
					
					
					setFlag(data.r3);
					//Sets Flag based on the new value of r3
				
				
				}
				
				
			}//end Immediate OR if statements
		
	}//end OR if statements
	
	
	else if (strcmp(opCode, "1000") == 0) {
	//NOT Command
	
	
		if (strcmp(regCode, "000") == 0){
		//NOT Command performed on register 0	
			
			
			data.r0 = ~data.r0;
			//Negates r0 and sets it to the negated value
			
			
			setFlag(data.r0);
			//Sets Flag based on the new value of r0
			
			
		}	
		
		
		else if (strcmp(regCode, "001") == 0){
		//NOT Command performed on register 1	
			
			
			data.r1 = ~data.r1;
			//Negates r1 and sets it to the negated value
			
			
			setFlag(data.r1);
			//Sets Flag based on the new value of r1
			
			
		}
		
		
		else if (strcmp(regCode, "010") == 0){
		//NOT Command performed on register 2	
			
			
			data.r2 = ~data.r2;
			//Negates r2 and sets it to the negated value
			
			
			setFlag(data.r2);
			//Sets Flag based on the new value of r2
			
			
		}
		
		
		else if (strcmp(regCode, "011") == 0){
		//NOT Command performed on register 3	
			
			
			data.r3 = ~data.r3;
			//Negates r3 and sets it to the negated value
			
			
			setFlag(data.r3);
			//Sets Flag based on the new value of r3
			
			
		}
		
		
	}//end NOT if statements
	
	
	else if(strcmp(opCode, "1001") == 0) {
	//JMP Command
	
	
		progCount = locationNum - 1;
		//Sets program count to the location given by the instruction
		
		
	}//end JMP if statement
	
	
	else if(strcmp(opCode, "1010") == 0) {
	//JEQ Command 
	
	
		if (strcmp(data.flag, "010") == 0)
		//Proceeds if flag condition is zero 
		

			progCount = locationNum - 1;
			//Jumps to the instruction given by the jump instruction
			
			
			
	}//end JEQ if statement
	
	
	else if(strcmp(opCode, "1011") == 0) {
	//JGT Command 
	
	
		if (strcmp(data.flag, "001") == 0)
		//Proceeds if flag condition is positive 
		

			progCount = locationNum - 1;
			//Jumps to the instruction given by the jump instruction
			
			
			
	}//end JGT if statement
	
	
	else if(strcmp(opCode, "1100") == 0) {
	//JLT Command 
	
	
		if (strcmp(data.flag, "100") == 0)
		//Proceeds if flag condition is negative 
		

			progCount = locationNum - 1;
			//Jumps to the instruction given by the jump instruction
			
			
			
	}//end JLT if statement
	
	
	else if(strcmp(opCode, "1101") == 0) {
	//Compare Command
	
	
		if (strcmp(regCode, "000") == 0){
		//Compare Command on register 0
		
		
			if(data.r0 == 0)
			//Proceeds if the value in r0 is 0
			
			
				setFlag(0);
				//Sets the flag condition to zero
				
			
			else if(data.r0 > 0)
			//Proceeds if the value in r0 is positive
			
			
				setFlag(1);
				//Sets the flag condition to positive
				
				
			else if(data.r0 < 0)
			//Proceeds if the value in r0 is negative
			
			
				setFlag(-1);
				//Sets the flag condition to negative
				
				
		}
		
		
		else if (strcmp(regCode, "001") == 0){
		//Compare Command on register 1
		
		
			if(data.r1 == 0)
			//Proceeds if the value in r1 is zero
			
			
				setFlag(0);
				//Sets the flag condition to zero
				
			
			else if(data.r1 > 0)
			//Proceeds if the value in r1 is positive
			
			
				setFlag(1);
				//Sets the flag condition to positive
				
				
			else if(data.r1 < 0)
			//Proceeds if the value in r1 is negative
			
			
				setFlag(-1);	
				//Sets the flag condition to negative
				
				
		}
		
		
		else if (strcmp(regCode, "010") == 0){
		//Compare Command on register 2
		
		
			if(data.r2 == 0)
			//Proceeds if the value in r2 is 0
			
			
				setFlag(0);
				//Sets the flag condition to zero
				
			
			else if(data.r2 > 0)
			//Proceeds if the value in r2 is positive
			
			
				setFlag(1);
				//Sets the flag condition to positive
				
				
			else if(data.r2 < 0)
			//Proceeds if the value in r2 is negative
			
			
				setFlag(-1);
				//Sets the flag condition to negative
				
				
		}
		
		
		else if (strcmp(regCode, "011") == 0){
		//Compare Command on register 3
		
		
			if(data.r3 == 0)
			//Proceeds if the value in r3 is 0
			
			
				setFlag(0);
				//Sets the flag condition to zero
				
			
			else if(data.r3 > 0)
			//Proceeds if the value in r3 is positive
			
			
				setFlag(1);
				//Sets the flag condition to positive
				
				
			else if(data.r3 < 0)
			//Proceeds if the value in r3 is negative
			
			
				setFlag(-1);	
				//Sets the flag condition to negative
				
				
		}
		
		
		else if (strcmp(opCode, "1110") == 0) {
		//Clear Command
		
		
			if (strcmp(regCode, "000") == 0){
			//Clear Command on register 0
			
				
				data.r0 = 0;
				//Clears r0 by setting it to 0
				
				
			}
			
			
			else if (strcmp(regCode, "001") == 0){
			//Clear Command on register 1
			
				
				data.r1 = 0;
				//Clears r1 by setting it to 0
				
				
			}
			
			
			else if (strcmp(regCode, "010") == 0){
			//Clear Command on register 2
			
				
				data.r2 = 0;
				//Clears r2 by setting it to 0
				
				
			}
			
			
			else if (strcmp(regCode, "011") == 0){
			//Clear Command on register 3
			
				
				data.r3 = 0;
				//Clears r3 by setting it to 0
				
				
			}
			
		}//end Clear if statements
			
		
	}//end Compare if statements
	
}//end execute


void dump(){
	
	int i = 0;
	
	
	printf("\n");
	//Prints a new line to seperate output
	
	
	printf("Execution:\n\nStarting at address 0x%02x:\n\n", sizeOfOffset);
	//Prints out the intial lines for the execution portion of the output
	
	
	printf("r0 - ");
	
	printBinaryNum(data.r0, WORD_LENGTH);
	//Prints out the binary representaion of the data in register 0
	
	printf("\n\n");
	
	
	
	printf("r1 - ");
	
	printBinaryNum(data.r1, WORD_LENGTH);
	//Prints out the binary representaion of the data in register 1
	
	printf("\n\n");
	
	
	
	printf("r2 - ");
	
	printBinaryNum(data.r2, WORD_LENGTH);
	//Prints out the binary representaion of the data in register 2
	
	printf("\n\n");
	
	
	
	printf("r3 - ");
	
	printBinaryNum(data.r3, WORD_LENGTH);
	//Prints out the binary representaion of the data in register 3
	
	printf("\n\n");
	
	
	
	printf("PC - ");
	
	printBinaryNum(progCount+1, COUNT_LENGTH);
	//Prints out the binary representaion of the program counter + 1, to show true value
	
	printf("\n\n");
	
	
	
	printf("IR - %s \n\n", data.instructionRegister);
	//Prints out the instruction register
	
	
	printf("CC - %s \n\n", data.flag);
	//Prints out the active condition code of the program's flag
	
	
	for (i = 0; i < MAX_WORDS; i++) {
	//
		
		if(i > numInstruc){
		//Checks to see if all the instructions have been printed out
		
			
			if(data.memory[i] != 0) {
			//Will print only non-zero number that appear after the instructions 
			
			
				printBinaryNum(data.memory[i], WORD_LENGTH);
				//Prints out the binary representation of the data at a spot in memory
			
			
				printf("\n");
			
			
			}
		
		}
	
		else {
			
		
			printBinaryNum(data.memory[i], WORD_LENGTH);
			//Prints out the binary representation of the data at a spot in memory
		
		
			printf("\n");
			
		}

	} // end for
	
}//end dump method



int convertInstr(char instr[], int length) { 
//Will  convert a bianry number to a decimal value
	
	
	int position;
	//Holds the position of the number being looked at
	
	
	int total = 0;
	//Stores the total decimal number being built
	 
	
	int exponent = 0; 
	//Will represent the position of where the for loop is pointing to in the binary number
	

	for (position = length -1; position >= 0; position--) {
	//Moves backwards to go through the array in reverse order, to start witht the smallest positon


		if (instr[position] == '1') {
		//Proceeds if at the current position, the binary number has a one
		
		
			total += powOfTwo(exponent);
			//Creates the decimal number
			

		} // end if
		

		exponent++; 
		//Increments exponent
		

	} // end for
	

	return total;
	//Returns the decimal representation of the passed in number
	

} // end convertInstr function



int powOfTwo(int exp) {
//Will return the value of two raised to the passed in exponent
	
	
	int result = 1;
	//Sets the result to 1, or 2 to the 0
	
	
	int i;
	//Stores the counter for the for loop
	
	
	for(i = 1; i <= exp; i++){
		
		
		result = result * 2;
		//Makes result go up by a power of two
		
		
	}//end for loop
	
	
	return result;
	//Returns 2 raised to the given value
	
	
}//end powOfTwo method


void makeBinaryNum(int numVal, int binLength){
//Will print out the binary representaion of an integer
	
	
	int position = binLength - 1;
	//Takes the length of the integer and uses it to represent a position in the number

	
	int binNum = 1 << (position - 1);
	//Creates a binary number that has a 1 as many spots to the left as position
		
	
	if(numVal < 0) {
	//Checks to see if the passed in number is less than zero
		
		
		numVal = ~numVal;
		//Gets the compliment of numVal
		
		
		numVal++;
		//Adds one to numVal to finish the conversion from two's compliment
				
	
	}//end if
	
	
	while (position >= 0) {
	

		if ((numVal & binNum)) {
			
			
			 newBin[position] = '1';
			 //Assigns a 1 if both the input number and binNum have an equal value
			 			 

		} // end if


		else {
			
			
			newBin[position] = '0';
			//Assigns a 0 if the two numbers do not have an equal value
			

		} // end else


		binNum >>= 1;
		//shifts the binNum by one to the right
		
		
		position--;
		//Decrements position by one 
	
	
	}//end while loop

	
}//end makeBinaryNum 

void printBinaryNum(int numVal, int binLength){
//Will print out the binary representaion of an integer
	
	
	int position = binLength;
	//Takes the length of the integer and uses it to represent a position in the number
	
	
	int binNum = 1 << (position - 1);
	//Creates a binary number that has a 1 as many spots to the left as position
	
	
	if(numVal < 0) {
	//Checks to see if the passed in number is less than zero
		
		
		numVal = ~numVal;
		//Gets the compliment of numVal
		
		
		numVal++;
		//Adds one to numVal to finish the conversion from two's compliment
				
	
	}//end if
	
	
		while (position > 0) {
			
	
			if ((numVal & binNum)) {
				
	
				 printf("1");
				 //Prints a 1 if both the input number and binNum have an equal value
				 
	
			} // end if
	
	
			else {
				
	
				printf("0");
				//Prints a 0 if the two numbers do not have an equal value
				
	
			} // end else
	
	
			binNum >>= 1;
			//shifts the binNum by one to the right
			
			
			position--;
			//Decrements position by one 
		
		
		}//end while loop
		
	
}//end printBinaryNum 


void setFlag(int passedIn){
	
	if((strcmp(opCode,"1001")) != 0 ||(strcmp(opCode,"1010")) != 0 || (strcmp(opCode,"1011")) != 0 || 
		(strcmp(opCode,"1100")) != 0 ) {
		//Proceeds if opCode is not a jump command
		
	
		if(passedIn == 0){
			
			strcpy(data.flag, "010");
			//makes flag show a zero condition
			
		}
		
		else if(passedIn > 0){
			
			strcpy(data.flag, "001");
			//makes flag show a positive condition
			
		}
		
		else if(passedIn < 0){
			
			strcpy(data.flag, "100");
			//makes flag show a negative condition
			
		}
				
	}//end if 
}//end setFlag condition


