#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HuffmanTreeNode {

public:

	char element;
	float weight;
	HuffmanTreeNode * parent;
	HuffmanTreeNode * leftChild;
	HuffmanTreeNode * rightChild;

	HuffmanTreeNode() {
		leftChild = NULL;
		rightChild = NULL;
	}

	HuffmanTreeNode(char x, float weight) {
		this->element = x;
		this->weight = weight;
		leftChild = NULL;
		rightChild = NULL;
	}

	HuffmanTreeNode(char x, HuffmanTreeNode * lc, HuffmanTreeNode *rc, float weight) {
		this->element = x;
		this->weight = weight;
		this->leftChild = lc;
		this->rightChild = rc;
	}

	HuffmanTreeNode(float weight) {
		this->weight = weight;
		this->element = ' ';
		this->leftChild = NULL;
		this->rightChild = NULL;
	}

	HuffmanTreeNode * getLeftChild() { return this->leftChild; }
	HuffmanTreeNode * getRightChild() { return this->rightChild; }

	void setLeftChild(HuffmanTreeNode *lc) { this->leftChild = lc; }
	void setRightChild(HuffmanTreeNode * rc) { this->rightChild = rc; }

	char getValue() { return this->element; }
	void setValue(char x) { this->element = x; }
	bool isLeaf() { return (this->leftChild == NULL && this->rightChild == NULL) ? true : false; }

};


class MinHeap {

public:

	HuffmanTreeNode** HeapArr;
	int curCount;

	MinHeap();
	~MinHeap();

	void BuildHeap(HuffmanTreeNode** arr, int num);
	void Insert(HuffmanTreeNode* x);
	void SiftDown(int inx);
	void SiftUp();
	HuffmanTreeNode* RemoveMin();
};

MinHeap::MinHeap() {
	HeapArr = new HuffmanTreeNode *[36];
}

MinHeap::~MinHeap() {
	delete[] HeapArr;
}

void MinHeap::BuildHeap(HuffmanTreeNode** arr, int num) {

	curCount = num;
	for (int i = 0; i < num; i++)
		HeapArr[i] = arr[i];

	for (int i = num / 2 - 1; i >= 0; i--)
		SiftDown(i);
}

void MinHeap::SiftDown(int inx) {

	int j = 2 * inx + 1;
	int temp = HeapArr[inx]->weight;
	HuffmanTreeNode* tmp = HeapArr[inx];

	while (j < curCount) {

		if (j < curCount - 1 && HeapArr[j]->weight > HeapArr[j + 1]->weight)
			j++;

		if (HeapArr[j]->weight < temp) {
			HeapArr[inx] = HeapArr[j];
			inx = j;
			j = 2 * j + 1;
		}
		else
			break;
	}

	HeapArr[inx] = tmp;
}

void MinHeap::SiftUp() {

	int inx = curCount;
	int tmp = -1, p = HeapArr[inx]->weight;
	HuffmanTreeNode * origin = HeapArr[inx];

	while (inx != 0) {
		tmp = inx / 2 - 1 + (inx % 2);
		if (HeapArr[tmp]->weight > p) {
			HeapArr[inx] = HeapArr[tmp];
			inx = tmp;
		}
		else
			break;
	}
	HeapArr[inx] = origin;
}

HuffmanTreeNode* MinHeap::RemoveMin() {

	HuffmanTreeNode* min = HeapArr[0];
	HeapArr[0] = HeapArr[curCount - 1];
	curCount--;

	for (int i = curCount / 2 - 1; i >= 0; i--)
		SiftDown(i);

	return min;
}

void MinHeap::Insert(HuffmanTreeNode* x) {

	HeapArr[curCount] = x;
	SiftUp();
	curCount++;
}



class HuffmanTree {

public:
	HuffmanTreeNode * root;

	HuffmanTree(float weight[], int n) {

		char c = 'A';
		MinHeap heap;
		HuffmanTreeNode** nodeList = new HuffmanTreeNode*[n];

		HuffmanTreeNode * parent, *lc, *rc;

		for (int i = 0; i < n; i++) {
			nodeList[i] = new HuffmanTreeNode(c + i,weight[i]);
			heap.Insert(nodeList[i]);
		}

		for (int i = 0; i < n - 1; i++) {
			parent = new HuffmanTreeNode;
			parent->leftChild = heap.RemoveMin();
			parent->rightChild = heap.RemoveMin();

			heap.Insert(parent);
			root = parent;
		}

		delete[] nodeList;

	}
};

void main() {

	float weight[8] = {0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};

	HuffmanTree hf(weight, 8);


}