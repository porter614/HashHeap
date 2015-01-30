#ifndef __hashHeap_H__
#define __hashHeap_H__


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

//==================================MIN HEAP DECLARATIONS==================================

class minHeap								
{
	private:
		int *data;
      	int heapSize;
      	int arraySize;

      	int getLeftChildIndex(int nodeIndex); 
      	int getRightChildIndex(int nodeIndex);
     	int getParentIndex(int nodeIndex);
     	void swap(int a, int b);
	public:
		minHeap(int size);
		~minHeap();
		int insert(int insert_key);
		int deletemin();
		int deleteint(int i);
		void percolatedown(int index);
		void percolateup(int index);
		void print();
};

//==================================HASH TABLE DECLARATIONS=================================

class hashNode 
{
	private:
		int key;
		int flag;
	public:
		hashNode(int i);
		int getkey() { return key;}
		int getflag() { return flag;}
		void setflag(int i) {flag = i;}
};

class hashTable 
{
	private:
		hashNode **list;
		int tableSize;
	public:
		hashTable(int size);
		int hashFunction(int key);
		int insert(int i);
		int lookup(int i);
		int deleteint(int i);
};

//==================================HASH-HEAP DECLARATIONS==================================

class hashHeap    								
{
	private:
		hashTable *table;
		minHeap *heap;
	public:
		hashHeap(int size);
		~hashHeap();
		int insert(int i);
		int lookup(int i);
		int deletemin();
		int deleteint(int i);
		void print();
};

//===========================================================================================

#endif;