#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "hashHeap.h"

using namespace std;

int main(int argc,char*argv[])
{
	int i,currentinstruction,commandcount,instructionresult;

	cin >> currentinstruction;														//Scan in the arraysize
	hashHeap *list = new hashHeap(currentinstruction);

	cin >> commandcount;															//Scan in number of commands

	for (i = 1;i<=commandcount;i++)
	{
		cin >> currentinstruction;
		if(currentinstruction == 0)													//Instruction 0: Call Insert
		{
			cin >> currentinstruction;												//Scan for element to insert
			instructionresult = list->insert(currentinstruction);
			if(instructionresult) cout << currentinstruction << " inserted\n";
			else cout << currentinstruction << " already present\n";
		}
		else if(currentinstruction == 1)											//Instruction 1: Call Lookup
		{																			//Scan for element to lookup
			cin >> currentinstruction;
			instructionresult = list->lookup(currentinstruction);
			if(instructionresult) cout << currentinstruction << " found\n"; 
			else cout << currentinstruction << " not found\n"; 
		}
		else if(currentinstruction == 2)											//Instruction 2: Call Deletemin
		{																			
			instructionresult = list->deletemin();
			cout << "Minimum key " << instructionresult << " deleted\n"; 
		}
		else if(currentinstruction == 3)											//Instruction 3: Call Delete Int
		{																			//Scan for element to delete
			cin >> currentinstruction;
			instructionresult = list->deleteint(currentinstruction);
			if(instructionresult) cout << currentinstruction << " deleted\n";
			else cout << currentinstruction << " not found\n"; 
		}
		else if(currentinstruction == 4)											//Instruction 4: Call Print
			list->print();															

		else break;
	}
	return 0;

}
