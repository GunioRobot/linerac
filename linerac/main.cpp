#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef unsigned short ushort;

double registers[12];						// Stores the 12 registers, that our "calculator" has
bool registersUsable[12];					// Remembers which registers are usable

void throwError(ushort,ostream&);			// Displays error message
bool isUsable(ushort);						// Checks if a register is usable

int main2()
{

	// Make all registers unusable
	for(int index = 0;index<12;index++)
		registersUsable[index] = false;		

	// Open input text
	ifstream inputFile;
	inputFile.open("input.txt");

	// go into a loop
	do
	{
		/*
			Lets assume a command is made out of parts, which are seperated by whitespace.
			In these terms, a command can be made of either two or three parts, so to get an idea about what our command will be, 
			we'll assume that it's a two piece command.
			After storing the pieces in memory, we will eventualy extract another piece *if* that is necesary.
		*/

		// Store first part in a variable

		// Store second part in a variable

		// if first part is a comma-seperated list of numbers
			// we count the ammount of numbers

			// we store the numbers (tokenization, where ',' is the token)

			// if the values of the numbers are invalid registers
				
				// error!
			
			
			// if the second part is a valid command

				// we check if the ammount of numbers does not equal the arity of the command
					
					// error!
				
				// if the chosen registers are unavailable
					
					// error!
				
				// we apply the command
			
			// error!
	}
	while(!inputFile.eof());
	// until you reach the end of the file




	return 0;
}

bool isUsable(ushort index)
{
	return registersUsable[index];
}