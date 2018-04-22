#include <iostream>
#include <string>

using namespace std;

class BinaryTreeNode {

public:

	char element;
	BinaryTreeNode * parent;
	BinaryTreeNode * leftChild;
	BinaryTreeNode * rightChild;

	BinaryTreeNode() {
		leftChild = NULL;
		rightChild = NULL;
	}

	BinaryTreeNode(char x) {
		this->element = x;
		leftChild = NULL;
		rightChild = NULL;
	}

	BinaryTreeNode(char x, BinaryTreeNode * lc, BinaryTreeNode *rc) {
		this->element = x;
		this->leftChild = lc;
		this->rightChild = rc;
	}

	BinaryTreeNode * getLeftChild() { return this->leftChild; }
	BinaryTreeNode * getRightChild() { return this->rightChild; }

	void setLeftChild(BinaryTreeNode *lc) { this->leftChild = lc; }
	void setRightChild(BinaryTreeNode * rc) { this->rightChild = rc; }

	char getValue() { return this->element; }
	void setValue(char x) { this->element = x; }
	bool isLeaf() {return (this->leftChild == NULL && this->rightChild == NULL) ? true : false;}
};


class ArrStack {

public:

	int maxSize;
	int top;
	BinaryTreeNode* (*st);

	ArrStack(int maxSize) {
		this->maxSize = maxSize;
		top = -1;
		st = new BinaryTreeNode*[this->maxSize];
	}

	~ArrStack() {}

	bool push(BinaryTreeNode * node) {
		if (top == this->maxSize - 1) {
			cout << "FULL Stack!" << endl;
			return false;
		}
		st[++top] = node;
		return true;
	}

	BinaryTreeNode* Pop() {
		if (top == -1) {
			cout << "FULL Stack" << endl;
			return NULL;
		}

		return st[top--];
	}

	BinaryTreeNode * Top() {
		if (top == -1) {
			cout << "FULL Stack!" << endl;
			return NULL;
		}

		return st[top];
	}

	bool isEmpty() { return (this->top == -1) ? true : false; }
};


class ArrQueue {

public:
	int maxSize;
	int front;
	int rear;
	BinaryTreeNode * (*q);

	ArrQueue(int maxSize) {
		this->maxSize = maxSize;
		q = new BinaryTreeNode *[this->maxSize];
		front = rear = 0;
	}

	~ArrQueue() {}

	bool EnQueue(BinaryTreeNode * node) {
		if ((rear + 1) % this->maxSize == front) {
			cout << "FULL Queue!" << endl;
			return false;
		}

		q[rear] = node;
		rear = (rear + 1) % this->maxSize;
		return true;
	}

	BinaryTreeNode * DeQueue() {
		if (front == rear) {
			cout << "EMPTY Queue!" << endl;
			return NULL;
		}

		BinaryTreeNode * node = q[front];
		front = (front + 1) % this->maxSize;
		return node;
	}

	BinaryTreeNode * GetFront() {
		if (front == rear) {
			cout << "EMPTY Queue!" << endl;
			return NULL;
		}

		BinaryTreeNode * node = q[front];
		return node;
	}

	bool isEmpty() { return (rear == front) ? true : false; }
};

class BinaryTree{

public:

	BinaryTreeNode * root;

	BinaryTree() {
		root = new BinaryTreeNode();
		root->leftChild = NULL;
		root->rightChild = NULL;
		root->parent = NULL;
	}

	~BinaryTree() {}

};

void pre_order_recur(BinaryTreeNode *root) {

	if (root != NULL) {
		cout << root->element << ' ';
		if (root->leftChild)
			pre_order_recur(root->leftChild);
		if (root->rightChild)
			pre_order_recur(root->rightChild);
	}
	else
		return;
}

void in_order_recur(BinaryTreeNode * root) {
	if (root != NULL) {
		if (root->leftChild)
			in_order_recur(root->leftChild);
		cout << root->element << ' ';
		if (root->rightChild)
			in_order_recur(root->rightChild);
	}
	else
		return;
}

void post_order_recur(BinaryTreeNode * root) {
	if (root != NULL) {
		if (root->leftChild)
			post_order_recur(root->leftChild);
		if (root->rightChild)
			post_order_recur(root->rightChild);
		cout << root->element << ' ';
	}
	else
		return;
}

void pre_order_basic(BinaryTreeNode *root) {

	ArrStack as(36);

	BinaryTreeNode *pointer = root;

	while (pointer || !as.isEmpty()) {
		if (pointer == NULL)
			pointer = as.Pop()->rightChild;
		else {
			cout << pointer->element << ' ';
			as.push(pointer);
			if (pointer->leftChild)
				pointer = pointer->leftChild;
			else
				pointer = as.Pop()->rightChild;
		}
	}

}

void in_order_basic(BinaryTreeNode *root) {
	ArrStack as(36);

	BinaryTreeNode *pointer = root;

	while (pointer || !as.isEmpty()) {
		
		if (pointer == NULL) {
			pointer = as.Pop();
			cout << pointer->element << ' ';
			pointer = pointer->rightChild;
		}
		else {
			for (; pointer; pointer = pointer->leftChild)
				as.push(pointer);

			pointer = as.Pop();
			cout << pointer->element << ' ';

			pointer = pointer->rightChild;
		}

	}

}

void post_order_basic(BinaryTreeNode * root) {

	ArrStack as(36);
	BinaryTreeNode *pointer = root;
	BinaryTreeNode *prev = NULL;

	while (pointer || !as.isEmpty()) {

		if (pointer && pointer->rightChild != prev) {

			for (; pointer; pointer = pointer->leftChild)
				as.push(pointer);

			pointer = as.Top()->rightChild;
		}

		else {
			pointer = as.Pop();
			cout << pointer->element << ' ';
			prev = pointer;

			if (as.isEmpty())
				break;
			if (as.Top()->rightChild != prev)
				pointer = as.Top()->rightChild;
			else
				pointer = as.Top();
		}
	}

}

void post_order_basic1(BinaryTreeNode * root) {
	ArrStack as(36);
	BinaryTreeNode *pointer = root;
	BinaryTreeNode *prev = NULL;

	while (pointer || !as.isEmpty()) {
		if (pointer) {
			as.push(pointer);
			pointer = pointer->leftChild;
		}

		else {
			if (as.Top()->rightChild && as.Top()->rightChild != prev)
				pointer = as.Top()->rightChild;
			else {
				cout << as.Top()->element << ' ';
				prev = as.Pop();
			}
		}
	}
}


void breadth_first(BinaryTreeNode *root) {

	ArrQueue aq(36);

	BinaryTreeNode *cur = root;
	if (cur)
		aq.EnQueue(cur);

	while (!aq.isEmpty()) {

		cur = aq.DeQueue();
		cout << cur->element << ' ';
		if (cur->leftChild)
			aq.EnQueue(cur->leftChild);
		if (cur->rightChild)
			aq.EnQueue(cur->rightChild);
	}
}

BinaryTreeNode * pre_inGetRoot(string pre_order, string in_order) {

	
	int count = 0, len = in_order.length();
	if (len == 1)
		return new BinaryTreeNode(pre_order[0]);

	BinaryTreeNode * root = new BinaryTreeNode(pre_order[0]);
	for (int i = 0; i < len; i++) {
		if (in_order[i] != root->element)
			count++;
		else
			break;
	}

	if (count == 0)
		root->leftChild = NULL;
	else{
		string left_in_order = in_order.substr(0, count);
		string left_pre_order = pre_order.substr(1, count);
		root->leftChild = pre_inGetRoot(left_pre_order, left_in_order);
	}

	if (count + 1 == len)
		root->rightChild = NULL;
	else {
		string right_in_order = in_order.substr(count + 1, len - count - 1);
		string right_pre_order = pre_order.substr(count + 1, len - count - 1);
		root->rightChild = pre_inGetRoot(right_pre_order, right_in_order);
	}
	return root;
}

BinaryTreeNode * post_inGetRoot(string post_order, string in_order) {

	int count = 0, len = in_order.length();
	if (len == 1)
		return new BinaryTreeNode(post_order[0]);

	BinaryTreeNode * root = new BinaryTreeNode(post_order[len - 1]);

	for (int i = 0; i < len; i++) {
		if (in_order[i] != root->element)
			count++;
		else
			break;
	}

	if (count > 0) {
		string left_in_order = in_order.substr(0, count);
		string left_post_order = post_order.substr(0, count);
		root->leftChild = post_inGetRoot(left_post_order, left_in_order);
	}

	if (count + 1 < len) {
		string right_in_order = in_order.substr(count + 1, len - count - 1);
		string right_post_order = post_order.substr(count, len - count - 1);
		root->rightChild = post_inGetRoot(right_post_order, right_in_order);
	}

	return root;
}



void main() {

	string pre_order = "ABDFGCEH";
	string in_order = "BFDGACEH";
	string post_order = "FGDBHECA";

	string str1 = "MGBJHSU";
	string str2 = "BGHJMSU";

	//BinaryTreeNode * root = pre_inGetRoot(pre_order, in_order);
	BinaryTreeNode * root = post_inGetRoot(post_order, in_order);
	//BinaryTreeNode * root = pre_inGetRoot(str1, str2);
	pre_order_basic(root);
	cout << endl;
	in_order_basic(root);
	cout << endl;
	post_order_basic1(root);
	cout << endl;
	breadth_first(root);
	cout << endl;
	
	
	
	system("pause");
}


