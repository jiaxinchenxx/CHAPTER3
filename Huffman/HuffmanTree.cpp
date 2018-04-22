#include <iostream>
#include <string>

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

class LinkedNode {

public:

	HuffmanTreeNode * node;
	LinkedNode * next;

};



class LinkedList {

public:

	LinkedNode * HEAD;

	LinkedList() { HEAD = new LinkedNode(); }

	~LinkedList() {
		LinkedNode * p = HEAD;
		LinkedNode * q = p;
		while (p) {
			q = p->next;
			delete p;
			p = q;
		}
	}

	void insert(HuffmanTreeNode * node);
	HuffmanTreeNode* getMin();

};

HuffmanTreeNode* LinkedList::getMin() {

	LinkedNode* p = HEAD->next;
	HEAD->next = HEAD->next->next;
	return p->node;

}

void LinkedList::insert(HuffmanTreeNode * node) {

	LinkedNode * tmp = new LinkedNode();
	tmp->node = node;
	tmp->next = NULL;
	

	if (HEAD->next == NULL) {
		HEAD->next = tmp;
		return;
	}

	LinkedNode * p = HEAD;
	LinkedNode * temp;
	bool isInserted = false;

	while (p->next) {
		if (p->next->node->weight > tmp->node->weight) {
			temp = p->next;
			p->next = tmp;
			tmp->next = temp;
			isInserted = true;
			break;
		}
		else
			p = p->next;
	}

	if (!isInserted)
		p->next = tmp;

}

class HuffmanTree {

public:

	HuffmanTreeNode * root;

	HuffmanTree(float weight[],  int n);


};

HuffmanTree::HuffmanTree(float weight[], int n) {

	LinkedList l1;
	char c = 'A';
	HuffmanTreeNode * p, *lc, *rc;

	for (int i = 0; i < n; i++) {

		HuffmanTreeNode* tmp = new HuffmanTreeNode(c + i, weight[i]);
		l1.insert(tmp);
	}

	for (int i = 0; i < n - 1; i++) {

		lc = l1.getMin();
		rc = l1.getMin();

		p = new HuffmanTreeNode(lc->weight + rc->weight);
		p->leftChild = lc;
		p->rightChild = rc;
		l1.insert(p);

		root = p;

	}
}

void main() {

	float weight[8] = { 0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11 };

	HuffmanTree hf(weight, 8);

}