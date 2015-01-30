#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "hashHeap.h"

using namespace std;

//=========================-------------------HEAP IMPLEMENTATION------------=========================	

minHeap::minHeap(int size)   //Min Heap Constructor
{
	data = new int[size];
	heapSize = 0;
	arraySize = size;
}

minHeap::~minHeap() 
{
    delete[] data;
}

int minHeap::getLeftChildIndex(int nodeIndex) 		//Returns Index of the Left Child
      	{
            return 2 * nodeIndex + 1;
     	}
 
int minHeap::getRightChildIndex(int nodeIndex) 		//Returns Index of the Right Child
      	{
            return 2 * nodeIndex + 2;
     	}
 
int minHeap::getParentIndex(int nodeIndex)			//Returns Index of the Parent
     	{
            return (nodeIndex - 1) / 2;
     	}

void minHeap::swap(int a, int b)					//Swaps two elements in the heap
{
	int tmp = data[a];
	data[a] = data[b];									
	data[b] = tmp;
	return;		
}

//=========================Heap Insert/Percolate Up and Down===============================================

int minHeap::insert(int i)
{
	heapSize += 1;    															//Increase Heap Size for new element
	data[heapSize - 1] = i;														//Insert New Element
	percolateup(heapSize-1);													//Percolate New Element up to its proper location
	return 0;
}

void minHeap::percolateup(int index)
{
	int i = data[index], tmp, currentindex = index,parent;
	if(currentindex == 0) return;    											//If the element is at the root, you are done.
	while(i < data[getParentIndex(currentindex)])   							//While the new element is less than its parent:
	{
		parent = getParentIndex(currentindex);      							//Update Parent's Index
		swap(parent,currentindex);												//Swap new element with its parent

		currentindex = parent;													//Update current index to parent index
		if(currentindex == 0) break;											//If the element is at the root, you are done.
	}
	return;
}

void minHeap::percolatedown(int index)
{
	int rightchild,leftchild,smallchild,tmp;
	while(1)
	{
		rightchild = getRightChildIndex(index);
		leftchild = getLeftChildIndex(index);
		if(rightchild >= heapSize && leftchild >= heapSize) return; 			//if current index has no children

		if(leftchild < heapSize && rightchild < heapSize)  						//if current index has 2 children
		{
			if(data[rightchild] < data[leftchild]) smallchild = rightchild;		//Decide which child to switch with
			else smallchild = leftchild;

			if(data[smallchild] < data[index])									//Decide if smaller child is less than parent
			{
				swap(smallchild,index);											//Swap if smaller child is less than the parent
				index = smallchild;												//Update current index
			}
			else break;
		}

		else if (leftchild < heapSize && rightchild >= heapSize) 				//if current index has only a left child
		{
			if(data[leftchild] < data[index])									//if left child is smaller than parent
			{
				swap(leftchild,index);											//Swap if left child is less than parent
				index = leftchild;												//Update current index
			}
			else break;
		}
	}
	return;
}


//=========================Heap DeleteMin/Int==========================================================

int minHeap::deletemin()     
{
	int returnvalue = data[0];								//Set return value to minimum element

	data[0] = data[heapSize-1];								//Replace minimum with the last element in the array
	data[heapSize-1] = '\0';								//Set last element to NULL

	heapSize--;												//Decrement the heap size
	percolatedown(0);										//Call percolate down on the root index
	return returnvalue;
}


int minHeap::deleteint(int i)
{
	int count, parent;
	for(count = 0; count < heapSize; count++) 				//Search the array
	{
		if(data[count] == i)								//If element to delete exists in the heap
		{
			data[count] = data[heapSize-1];					//Replace element with last element in the array
			data[heapSize-1] = '\0';						//Set last element to NULL
			heapSize--;										//Decrement heap size
			percolatedown(count);							//Call percolate down on the index of the deleted element

			for(count = 0; count < heapSize; count++)		//Percolate up all elements to their correct locations
				percolateup(count);
			break;
		}
	}
	return i;												//Return Deleted Item
}

//=========================Heap Print==========================================================

void minHeap::print()
{
	int i,count=0;
	minHeap *ptr = new minHeap(arraySize);					//Create temporary array
	ptr->heapSize = heapSize;

	for( i = 0; i < ptr->heapSize; i++) 					//Copy array into a temporary array
		ptr->data[i] = data[i];

	while(1) 
	{
		count++;
		if(ptr->heapSize == 0) 								//If there are no elements left to delete
		{
			delete[] ptr->data;								//Free allocated Memory 
			break;											//Exit loop
		}
		cout << ptr->data[0] << " ";						//Print out current miminum element
		ptr->deletemin();									//Delete current minimum element

	}
	cout << endl;											//When finished print a new line
}

//===========================================HASHTABLE IMPLEMENTATION==================================

hashNode::hashNode(int i)
{
	key = i;
	flag = 1;
}

hashTable::hashTable(int size)
{
	int i;
	tableSize = size;
	list = new hashNode* [size];
	for (i = 0 ; i < size ; i++) 
		list[i] = NULL;
}

int hashTable::hashFunction(int key)
{
	return key % tableSize;
}

//=========================================Hash Insert=========================================

int hashTable::insert(int key) 
{
    if (lookup(key) == 1) return 0;															//If key is already in the table return false
	int hash = hashFunction(key), count = 0;
    if (hash < 0) hash = hash * (-1);														//If key is a negative number, negate hash location
	while (list[hash] != NULL && list[hash]->getkey() != key && list[hash]->getflag() == 1 && count < tableSize)
    { 
        hash++;																				//Increment Hash and continue search
        if(hash == tableSize) hash = 0;														//Reset Hash to Zero if necessary
        count++;
    }
    if (lookup(key) == 1) return 0;
    list[hash] = new hashNode(key);
    
    return 1;
}

//=========================================Hash Lookup=========================================

int hashTable::lookup(int key) 
{  
    int hash = hashFunction(key), count = 0;
    if (hash < 0) hash = hash * (-1);														//If key is a negative number, negate hash location
       
    while (list[hash] != NULL && list[hash]->getkey() != key && count < tableSize)			//Search until you reach a NULL, or the key already exists
    {     									
        hash++;																				//Increment Hash and continue search
        if(hash == tableSize) hash = 0;														//Reset Hash to Zero if necessary
        count++; 
    }
    if (list[hash] == NULL || count >= tableSize || list[hash]->getflag() == 0) return 0;	//If you reached a NULL return false.
    else return 1;
}


//=========================================Hash Delete Int=======================================

int hashTable::deleteint(int key) 
{	
    int hash = hashFunction(key), count = 0;
    if (hash < 0) hash = hash * (-1);														//If key is a negative number, negate hash location
    while (list[hash] != NULL && list[hash]->getkey() != key && count < tableSize) 			//If you reach NULL or have searched the whole table, stop.
    {
        hash++;																				//Increment Hash and continue search
        if(hash == tableSize) hash = 0;														//Reset Hash to Zero if necessary
        count++;
    }
    if (list[hash]==NULL) return 0;															//If key is not currently in the table, return false.
    if (list[hash]->getkey() == key && list[hash]->getflag() == 1) 							//If key is found and it is not flagged, 
    { 																								
        list[hash]->setflag(0);																//flag key and return true.
        return 1;
    }
    else if (list[hash]->getkey() == key && list[hash]->getflag() == 0) return 0;			//If key is found but it is flagged as 'deleted' return false.
    return 0;
}
    
//=========================================HASH-HEAP IMPLEMENTATION================================

hashHeap::hashHeap(int size)			//Allocates space for a new heap and hash table.
{
	table = new hashTable(size);
	heap = new minHeap(size);
}

hashHeap::~hashHeap()
{
	delete [] table;
	delete [] heap;
}

int hashHeap::insert(int i)				//Inserts into hash table. If successful, insert into heap. 
{
	int result = table->insert(i);
	if(result) 
	{
		heap->insert(i);
		return 1;
	}
	return 0;
}

int hashHeap::lookup(int i)				//Looks up the element in the hash table.
{
	return table->lookup(i);
}

int hashHeap::deletemin()				//Calls deletemin on the heap and stores return result into a variable.
{										//The hash table deletes that variable
	int min = heap->deletemin();
	table->deleteint(min);
	return min;
}

int hashHeap::deleteint(int i)			//Deletes from hash table. If successful, deletes from heap.
{
	int result = table->deleteint(i);
	if(result)
	{
		heap->deleteint(i);
		return 1;
	}
	return 0;
}

void hashHeap::print()					//Calls print on heap
{
	heap->print();
}












