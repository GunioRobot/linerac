/* 
	Made in Visual Studio 2010
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef unsigned short ushort;

double registers[12];										// Stores the 12 registers, that our "calculator" has
bool registersUsable[12];									// Remembers which registers are usable

/* [TODO: Implement the error handling] */
void throwError(ushort,ostream&);							// Displays error messages
void throwError(ushort,ostream&,int*&,ushort&);
bool areValidRegisters(ushort*&,ushort);
bool isValidRegister(ushort);								// Checks if a register is valid and usable

void storeWhitespaceSeperated(istream&,string&,string&);	// Gets the next two commands from the input stream

bool isSwapCommand(string&);								// Checks if the given string is a swap command
bool isCommandInBeginning(string&);
bool isCommandAtEnd(string&);

ushort getArity(string&);									// Gets the arity of a command

bool isCommaSeperatedNumbersList(string&);					// Checks if a list is a list of numbers and commas, that doesn't begin or end with a comma

bool isNumber(string);	/*[Obsolete?]*/

ushort countNumbersInCommaSeperatedList(string&);			// Counts the amount of numbers in a list

void storeNumbers(string&,ushort*&,ushort&);						// Converts a variable ammount of comma-seperated values and saves them inside an array
void storeNumbers(string&,ushort&);							// Converts a single value to an integer
void storeNumbers(string&,ushort&,ushort&);						// Converts two comma-seperated values to an integer
void storeNumbers(string&,ushort&,ushort&,ushort&);					// Converts three comma-seperated values to integers

int main()
{
	string firstPart,secondPart,thirdPart;

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
		storeWhitespaceSeperated(inputFile,firstPart,secondPart);

		// if first part is a command
		if(isCommandInBeginning(firstPart))
		{
			// we store the arity of the command
			ushort arity = getArity(firstPart);

			// if second part is a comma-seperated list of numbers
			if(isCommaSeperatedNumbersList(secondPart))
			{
				// if the ammount of numbers is different than the arity of the command
				if (arity!=countNumbersInCommaSeperatedList(secondPart))				
					throwError(0,cout);					// error!

				/* [TODO: Implement memory component in the error management system; Currently memory gets freed at end of this if] */
				ushort* functionVariable = new ushort[arity];

				/* [TODO: Rethink the whole numbers storing 'mechanic'] */
				storeNumbers(secondPart,functionVariable,arity);

				if(!areValidRegisters(functionVariable,arity))
				{
					throwError(0,cout);
				}

				// apply the command
				cout << "Apply command" << endl;

				delete [] functionVariable;	// Clean up after ourselves...
			}
			else			// else second part is not a comma-seperated list, so error!
			{
				throwError(0,cout);
			}
		}
		// else if first part is a comma-seperated list of numbers
			// we count the ammount of numbers

			// we store the numbers (tokenization, where ',' is the token)

			// if the values of the numbers are invalid registers
				
				// error!
			
			
			// if the second part is a valid command

				// we check if the ammount of numbers does not equal the arity of the command
					
					// error!
				
				// if the chosen registers are unavailable
					
					// error!
				
				// if the command is the <> command

					// Store the third part in a variable

				// apply the command
			
			// error!
	}
	while(!inputFile.eof());	// while end-of-file not reached

	return 0;
}

// Cheks if a register is usable
bool isValidRegister(ushort index)
{
	return registersUsable[index] && index>=0 && index<=12;
}

// Checks if a range of registers are all usable
bool areValidRegisters(ushort* &registers,ushort arity)
{
	for(int i = 0;i<arity;i++)
		if(!isValidRegister(registers[i]))
			return false;

	return true;
}

void throwError(ushort errorCode,ostream& stream)
{
	stream << "Error type " << errorCode << ' ';
}

void throwError(ushort errorCode,ostream& stream,int* &data,ushort& length)
{
	throwError(errorCode,stream);
	stream << "for arguments: ";
	
	for(int i =0;i<length;i++)
	{
		stream << data[i];

		if(i==length-1)
			cout << endl;
		else
			cout << ' ';

	}

	delete [] data;
}


// Gets first two elements of a command
void storeWhitespaceSeperated(istream& stream,string& firstPart ,string& secondPart)
{
	char buffer[255];

	stream.getline(buffer,255,' ');
	firstPart = buffer;

	stream.getline(buffer,255,' ');
	secondPart = buffer;
}

// Determins if a string is a swap operation
bool isSwapCommand(string& operation)
{
	return operation.compare("<>")==0;
}

bool isCommandInBeginning(string& operation)
{
	return
		operation.compare("LC")==0 ||
		operation.compare("?")==0  ||
		operation.compare("+")==0  ||
		operation.compare("*")==0  ||
		operation.compare("#")==0 ;
}

bool isCommandAtEnd(string& operation)
{
	return
		operation.compare("-")==0  ||
		operation.compare("\\")==0 ||
		operation.compare("%")==0 ;
}

// Returns the arity of a command
ushort getArity(string& command)
{
	if(command.size()==1)
	{
		if(command.compare("?")==0)
			return 1;
	
		return 3;
	}
	else if(command.size()==2)
		return 2;

	return -1;
}


bool isCommaSeperatedNumbersList(string& list)
{
	/* 
		A comma seperated list of numbers can contain only numbers and commas 
		and can't begin or end with a comma
	*/

	for(int index = 0;index<list.size();index++)					// We iterate over the list
	{
		if(index==0 || index==list.size()-1)						// If we are at first or last place
			if(list[index]==',')									// ...and the element is a comma...
				return false;										// then we don't have a proper list

		if(list[index]<'0' && list[index]>'9' && list[index]!=',')	// If the current selected element is not a number and is not a comma
			return false;											// then we don't have a proper list
	}

	return true;
}

// Counts the ammount of numbers in a list
ushort countNumbersInCommaSeperatedList(string& list)
{
	/* 
		If a list is made out of numbers, seperated by commas, the ammount of numbers in that list is equal to 
		the ammount of comas +1, because there is a number after the last comma
	*/

	int commasCount = 0;						//Assume it's a one-number list

	for(int index=0;index<list.size();index++)	//Go over the list
	{
		if(list[index]==',')					// If we come across a comma
			commasCount++;						// increas counter
	}

	return commasCount+1;
}

// If a list is made out of one number
void storeNumbers(string& list,ushort& returnValueA)
{
	returnValueA = atoi(list.c_str());	// Pass the c-style string to the standard function
}

// If a list is made out of two numbers
void storeNumbers(string& list,ushort& returnValueA, ushort& returnValueB)
{
	auto commaSeperator = list.begin();	// We are gonna find where our comma is; Start looking from the start

	do
	{
		commaSeperator++;				// Go forward
	}
	while(*commaSeperator!=',');		// Until we find the comma

	storeNumbers(string(list.begin(),commaSeperator),returnValueA);	// We store the value left of the comma in returnValueA
	storeNumbers(string(commaSeperator+1,list.end()),returnValueB);	// We store the value to the right of the comma in returnValueB
}

// If a list is made out of three numbers
void storeNumbers(string& list,ushort& returnValueA, ushort& returnValueB, ushort& returnValueC)
{
	auto commaSeperator = list.begin();	// Start looking for the first comma from the start	

	do
	{
		commaSeperator++;				// Go forward
	}
	while(*commaSeperator!=',');		// Until we find the comma

	storeNumbers(string(list.begin(),commaSeperator),returnValueA);					// The value to the left of the comma is a 1-element list, so we pass it to the corresponding function 
	storeNumbers(string(commaSeperator+1,list.end()),returnValueB, returnValueC);	// The value to the left of the comma is a 2-element list, so we pass it to the corresponding function
}

void storeNumbers(string& list,ushort* &inputArray,ushort& arity)
{
	switch(arity)
	{
	case 1:
		storeNumbers(list,inputArray[0]);
		break;
	case 2:
		storeNumbers(list,inputArray[0],inputArray[1]);
		break;
	case 3:
		storeNumbers(list,inputArray[0],inputArray[1],inputArray[2]);
		break;
	}
}