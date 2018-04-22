#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MinHeap {

public:

	int* HeapArr;
	int curCount;

	MinHeap();
	~MinHeap();

	void BuildHeap(int * arr, int num);
	void Insert(int x);
	void SiftDown(int inx);
	void SiftUp();
	int RemoveMin();
};

MinHeap::MinHeap() {
	HeapArr = new int[36];
}

MinHeap::~MinHeap() {
	delete[] HeapArr;
}

void MinHeap::BuildHeap(int *arr, int num) {

	curCount = num;
	for (int i = 0; i < num; i++)
		HeapArr[i] = arr[i];
	for (int i = num / 2 - 1; i >= 0; i--)
		SiftDown(i);
}

void MinHeap::SiftDown(int inx) {

	int j = 2 * inx + 1;
	int temp = HeapArr[inx];

	while (j < curCount) {

		if (j < curCount - 1 && HeapArr[j] > HeapArr[j + 1])
			j++;

		if (HeapArr[j] < temp) {
			HeapArr[inx] = HeapArr[j];
			inx = j;
			j = 2 * j + 1;
		}
		else
			break;
	}

	HeapArr[inx] = temp;
}

void MinHeap::SiftUp(){

	int inx = curCount;
	int tmp = -1, p = HeapArr[inx];

	while (inx != 0) {
		tmp = inx / 2 - 1 + (inx % 2);
		if (HeapArr[tmp] > p) {
			HeapArr[inx] = HeapArr[tmp];
			inx = tmp;
		}
		else
			break;
	}
	HeapArr[inx] = p;
}

int MinHeap::RemoveMin() {

	int min = HeapArr[0];
	HeapArr[0] = HeapArr[curCount - 1];
	curCount--;

	for (int i = curCount / 2 - 1; i >= 0; i--)
		SiftDown(i);

	return min;
}

void MinHeap::Insert(int x) {

	HeapArr[curCount] = x;
	SiftUp();
	curCount++;
}


class HuffmanTreeNode {

public :

	char element;
	HuffmanTreeNode * parent;
	HuffmanTreeNode * leftChild;
	HuffmanTreeNode * rightChild;

	HuffmanTreeNode() {
		leftChild = NULL;
		rightChild = NULL;
	}

	HuffmanTreeNode(char x) {
		this->element = x;
		leftChild = NULL;
		rightChild = NULL;
	}

	HuffmanTreeNode(char x, HuffmanTreeNode * lc, HuffmanTreeNode *rc) {
		this->element = x;
		this->leftChild = lc;
		this->rightChild = rc;
	}

	HuffmanTreeNode * getLeftChild() { return this->leftChild; }
	HuffmanTreeNode * getRightChild() { return this->rightChild; }

	void setLeftChild(HuffmanTreeNode *lc) { this->leftChild = lc; }
	void setRightChild(HuffmanTreeNode * rc) { this->rightChild = rc; }

	char getValue() { return this->element; }
	void setValue(char x) { this->element = x; }
	bool isLeaf() { return (this->leftChild == NULL && this->rightChild == NULL) ? true : false; }

};

class HuffmanTree {

public:
	HuffmanTreeNode * root;

	HuffmanTree(float weight[], int n) {

		MinHeap heap;


	}



};

void main()
{
	int i, min;
	int arr[10] = { 20,12,35,15,10,80,30,17,2,1 };
	MinHeap heap;
	heap.BuildHeap(arr, 10);
	heap.Insert(0);
	min = heap.RemoveMin();
	for (i = 0; i<heap.curCount; i++)
		cout << heap.HeapArr[i] << endl;

	system("pause");
}




